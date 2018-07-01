
#include "FT_Platform.h"
#include "FT_Esd_Dl.h"

#include <stdio.h>
#define _USE_MATH_DEFINES 1
#include <math.h>
#define M_PI 3.14159265
extern ft_uint8_t Ft_Esd_LoopState;
extern ft_int16_t FT_DispWidth;
extern ft_int16_t FT_DispHeight;

extern Ft_Gpu_Hal_Context_t *Ft_Esd_Host;
extern Ft_Esd_GpuAlloc *Ft_Esd_GAlloc;

Ft_Esd_GpuState_T Ft_Esd_GpuState[FT_ESD_STATE_STACK_SIZE];
ft_uint8_t Ft_Esd_GpuState_I;
ft_uint32_t Ft_Esd_CoFgColor;
ft_uint32_t Ft_Esd_CoBgColor;
Ft_Esd_Rect16 Ft_Esd_ScissorRect;

// Number of bitmap handles to use (and also the scratch handle)
#ifdef FT_81X_ENABLE
#define FT_ESD_BITMAPHANDLE_NB 1UL
#else
#define FT_ESD_BITMAPHANDLE_NB 16UL
#endif
// List which bitmap info is using a handle
Ft_Esd_BitmapInfo *Ft_Esd_BitmapHandleInfo[FT_ESD_BITMAPHANDLE_NB] = { 0 };
Ft_Esd_GpuHandle Ft_Esd_BitmapHandleGpuHandle[FT_ESD_BITMAPHANDLE_NB] = { 0 };
ft_bool_t Ft_Esd_BitmapHandleUse[FT_ESD_BITMAPHANDLE_NB] = { 0 };
#ifdef FT_81X_ENABLE
ft_uint8_t Ft_Esd_ScratchHandle = 15;
#define FT_ESD_SCRATCHHANDLE (Ft_Esd_ScratchHandle)
#else
#define FT_ESD_SCRATCHHANDLE (15)
#endif

ft_bool_t Ft_Esd_BitmapHandleResized[FT_ESD_BITMAPHANDLE_NB] = { 0 };
ft_uint8_t Ft_Esd_BitmapHandlePage[FT_ESD_BITMAPHANDLE_NB] = { 0 };

#define FT_ESD_FONTHANDLE_NB 16UL // First font handle
#define FT_ESD_ROMFONT_NB 35UL
ft_uint8_t Ft_Esd_RomFontHandles[FT_ESD_ROMFONT_NB - FT_ESD_FONTHANDLE_NB] = { 0 };

void Ft_Esd_InitDlState()
{
	memset(Ft_Esd_BitmapHandleGpuHandle, 0, sizeof(Ft_Esd_BitmapHandleGpuHandle));
}

void Ft_Esd_ResetGpuState() // Begin of frame
{
	Ft_Esd_GpuState_I = 0;
	Ft_Esd_GpuState[0] = (Ft_Esd_GpuState_T) {
		.ColorA = 0xFF,
		.ColorRGB = 0xFFFFFF,
		.Handle = FT_ESD_BITMAPHANDLE_INVALID,
#ifdef FT_81X_ENABLE
		.VertexFormat = 4,
#endif
	};

	for (int i = 0; i < FT_ESD_BITMAPHANDLE_NB; ++i)
	{
		// 2: In use last frame
		// 1: Not in use anymore
		// 0: Not in use
		if (Ft_Esd_BitmapHandleUse[i] < 2)
			Ft_Esd_BitmapHandleUse[i] = 0;
		else
			--Ft_Esd_BitmapHandleUse[i];
		// 2: In use this frame
		// 1: In use last frame
		// 0: Not in use
	}

	// Reset scissor state to display size
	Ft_Esd_ScissorRect.X = 0;
	Ft_Esd_ScissorRect.Y = 0;
	Ft_Esd_ScissorRect.Width = FT_DispWidth;
	Ft_Esd_ScissorRect.Height = FT_DispHeight;
}

void Ft_Esd_ResetCoState()
{
	Ft_Esd_CoFgColor = 0x003870;
	Ft_Esd_CoBgColor = 0x002040;
}

ft_uint32_t Ft_Esd_BitmapHandle_GetTotalUsed()
{
	ft_uint32_t total = 0;
	for (int i = 0; i < FT_ESD_BITMAPHANDLE_NB; ++i)
	{
		if ((i != FT_ESD_SCRATCHHANDLE) && (Ft_Esd_BitmapHandleUse[i] > 0))
		{
			++total;
		}
	}
	return total;
}

ft_uint32_t Ft_Esd_BitmapHandle_GetTotal()
{
	return FT_ESD_BITMAPHANDLE_NB - 1; // NB minus one used for scratch
}

void FT_Esd_Render_Rect_Grad(ft_int16_t x, ft_int16_t y, ft_int16_t w, ft_int16_t h, ft_uint32_t color1, ft_uint32_t color2, ft_int16_t direction)
{
	if (color1 == color2) 
	{
	//	return FT_Esd_Render_Rect(x, y, w, h);
		 FT_Esd_Render_Rect(x, y, w, h);
	}
	
	double radius = direction * M_PI / 180.0f; 
	double sine = sin(radius), cosine = cos(radius);
	ft_int16_t x0 = x + (w >> 1);
	ft_int16_t y0 = y + (h >> 1);
	ft_int16_t l = sqrt(w*w + h*h) * 0.8; // use 80% to apply gradient effect
	ft_int16_t half = l >> 1;
	ft_int16_t dy = (ft_int16_t)(half * sine); 
	ft_int16_t dx = (ft_int16_t)(half * cosine);

	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, SAVE_CONTEXT());
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, SCISSOR_XY(x, y));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, SCISSOR_SIZE(w, h)); 	
	Ft_Gpu_CoCmd_Gradient(Ft_Esd_Host, x0 - dx, y0 - dy, color1, x0 + dx, y0 + dy, color2);
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, RESTORE_CONTEXT());
}

void FT_Esd_Render_Rect(ft_int16_t x, ft_int16_t y, ft_int16_t w, ft_int16_t h)
{
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BEGIN(RECTS));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, VERTEX2II(x, y, 0, 0));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, VERTEX2II(x + w, y + h, 0, 0));
}

ft_void_t Ft_Esd_Cmd_Button(ft_int16_t x, ft_int16_t y, ft_int16_t w, ft_int16_t h, ft_int16_t font, ft_uint16_t options, const ft_char8_t* s)
{
	Ft_Gpu_CoCmd_Button(Ft_Esd_Host, x, y, w, h, font, options, s);
}

ft_void_t Ft_Esd_Cmd_Number(ft_int16_t x, ft_int16_t y, ft_int16_t font, ft_uint16_t options, ft_int32_t n)
{
	Ft_Gpu_CoCmd_Number(Ft_Esd_Host, x, y, font, options, n);
}

void Ft_Esd_Dl_Bitmap_Page(ft_uint8_t handle, ft_uint8_t page)
{
	if (handle < FT_ESD_BITMAPHANDLE_NB && Ft_Esd_BitmapHandlePage[handle] != page)
	{
		Ft_Esd_BitmapInfo *info = Ft_Esd_BitmapHandleInfo[handle];
		ft_uint32_t addr = Ft_Esd_GpuAlloc_Get(Ft_Esd_GAlloc, Ft_Esd_BitmapHandleGpuHandle[handle]);
		Ft_Esd_Dl_BITMAP_HANDLE(handle);
		ft_uint32_t pageAddr = addr + ((((ft_uint32_t)page) << 7) * info->Stride * info->Height);
		Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BITMAP_SOURCE(pageAddr));
		Ft_Esd_BitmapHandlePage[handle] = page;
	}
}

void Ft_Esd_Dl_CELL_Paged(ft_uint8_t handle, ft_uint16_t cell)
{
	Ft_Esd_Dl_BITMAP_HANDLE(handle);
	Ft_Esd_Dl_Bitmap_Page(handle, cell >> 7);
	Ft_Esd_Dl_CELL(cell & 0x7F);
}

/*
ft_uint8_t Ft_Esd_Dl_Bitmap_Setup(Ft_Esd_BitmapInfo *bitmapInfo)
{
	// Get bitmap address
	ft_uint32_t addr = Ft_Esd_LoadBitmap(bitmapInfo);
	if (addr == ~0)
		return FT_ESD_BITMAPHANDLE_INVALID; // Bitmap not loaded (out of memory or file not found)

	ft_uint32_t handle = bitmapInfo->BitmapHandle;
	if (!((handle < FT_ESD_BITMAPHANDLE_NB)
		&& (handle != FT_ESD_SCRATCHHANDLE)
		&& (Ft_Esd_BitmapHandleInfo[handle] == bitmapInfo)
		&& (Ft_Esd_BitmapHandleGpuHandle[handle].Id == bitmapInfo->GpuHandle.Id)
		&& (Ft_Esd_BitmapHandleGpuHandle[handle].Seq == bitmapInfo->GpuHandle.Seq)))
	{
		// Bitmap is loaded but no handle is setup, create a new handle for this bitmap
		// ESD_print("Find free bitmap handle for addr %i\n", (int)addr);
		
		if (Ft_Esd_LoopState != ESD_LOOPSTATE_RENDER)
		{
#ifndef NDEBUG
			ESD_print("Warning: Can only setup bitmap during render pass\n");
#endif
			return FT_ESD_BITMAPHANDLE_INVALID;
		}

		// Find a free handle
		handle = FT_ESD_SCRATCHHANDLE; // Fallback to scratch handle
		for (int i = 0; i < FT_ESD_BITMAPHANDLE_NB; ++i)
		{
			if ((i != FT_ESD_SCRATCHHANDLE) && (!Ft_Esd_BitmapHandleUse[i]))
			{
				// Attach this handle to the bitmap info
				handle = i;
				Ft_Esd_BitmapHandleInfo[i] = bitmapInfo;
				Ft_Esd_BitmapHandleGpuHandle[i] = bitmapInfo->GpuHandle;
				break;
			}
		}
		
#ifndef NDEBUG
		ESD_print("Use handle %i, addr %i, gpu alloc %i, %i, file %s\n",
			(int)handle, (int)addr, (int)bitmapInfo->GpuHandle.Id, (int)bitmapInfo->GpuHandle.Seq,
			bitmapInfo->File ? bitmapInfo->File : "");
#endif

		bitmapInfo->BitmapHandle = handle;
		
		// Setup the handle
		Ft_Esd_Dl_BITMAP_HANDLE(handle);
		ft_uint32_t format = bitmapInfo->Format;
		if (format == DXT1) format = L1;
		else if (format == JPEG) format = RGB565; // TODO: Support for grayscale
		else if (format == PNG) format = RGB565; // TODO: Support for other PNG formats
		Ft_Gpu_CoCmd_SetBitmap(Ft_Esd_Host, addr, format, bitmapInfo->Width, bitmapInfo->Height); // TODO: What with stride?
		Ft_Esd_BitmapHandleResized[handle] = 0;
		Ft_Esd_BitmapHandlePage[handle] = 0;
	}

	// TEMPORARY WORKAROUND: SetBitmap not correctly being applied some frames... Need to check!
	// Ft_Esd_Dl_BITMAP_HANDLE(handle);
	// ft_uint32_t format = bitmapInfo->Format;
	// if (format == DXT1) format = L1;
	// else if (format == JPEG) format = RGB565; // TODO: Support for grayscale
	// else if (format == PNG) format = RGB565; // TODO: Support for other PNG formats
	// Ft_Gpu_CoCmd_SetBitmap(Ft_Esd_Host, addr, format, bitmapInfo->Width, bitmapInfo->Height); // TODO: What with stride?
	// Ft_Esd_BitmapHandleResized[handle] = 0;

	if ((handle < FT_ESD_BITMAPHANDLE_NB) && (handle != FT_ESD_SCRATCHHANDLE)) // When valid and not using scratch handle
	{
		Ft_Esd_BitmapHandleUse[handle] = 2; // In use
	}

#ifdef FT_81X_ENABLE
	// Use palette if available
	ft_uint32_t paletteAddr = Ft_Esd_LoadPalette(bitmapInfo);
	if (paletteAddr != ~0 && bitmapInfo->Format != PALETTED8) // PALETTED8 uses custom palette setup
	{
		Ft_Esd_Dl_PALETTE_SOURCE(paletteAddr);
	}
#endif

	return handle;
}
*/
ft_uint8_t Ft_Esd_Dl_RomFont_Setup(ft_uint8_t font)
{
	if (font >= FT_ESD_FONTHANDLE_NB && font < FT_ESD_ROMFONT_NB)
	{
		ft_uint8_t handle = Ft_Esd_RomFontHandles[font - FT_ESD_FONTHANDLE_NB];
		
		if (!(handle < FT_ESD_BITMAPHANDLE_NB
			&& (handle != FT_ESD_SCRATCHHANDLE)
			&& (Ft_Esd_BitmapHandleInfo[handle] == 0)
			&& (Ft_Esd_BitmapHandleGpuHandle[handle].Id == MAX_NUM_ALLOCATIONS)
			&& (Ft_Esd_BitmapHandleGpuHandle[handle].Seq == font)))
		{
			// The handle is no longer valid, make a new one
			
			// Find a free handle
			handle = FT_ESD_SCRATCHHANDLE; // Fallback to scratch handle
			for (int i = 0; i < FT_ESD_BITMAPHANDLE_NB; ++i)
			{
				if ((i != FT_ESD_SCRATCHHANDLE) && (!Ft_Esd_BitmapHandleUse[i]))
				{
					// Attach this handle to the bitmap info
					handle = i;
					Ft_Esd_BitmapHandleInfo[i] = 0;
					Ft_Esd_BitmapHandleGpuHandle[i].Id = MAX_NUM_ALLOCATIONS;
					Ft_Esd_BitmapHandleGpuHandle[i].Seq = font;
					break;
				}
			}

#ifndef NDEBUG
			ESD_print("Use handle %i, font %i\n",
				(int)handle, (int)font);
#endif
			
			// Set the font
			Ft_Esd_RomFontHandles[font - FT_ESD_FONTHANDLE_NB] = handle;
			Ft_Gpu_CoCmd_RomFont(Ft_Esd_Host, handle, font);
			FT_ESD_STATE.Handle = handle;
			Ft_Esd_BitmapHandleResized[handle] = 0;
			Ft_Esd_BitmapHandlePage[handle] = 0;
		}
		
		if ((handle < FT_ESD_BITMAPHANDLE_NB) && (handle != FT_ESD_SCRATCHHANDLE)) // When valid and not using scratch handle
		{
			Ft_Esd_BitmapHandleUse[handle] = 2; // In use
		}
		
		return handle;
	}
	return font;
}

void Ft_Esd_Dl_Bitmap_WidthHeight(ft_uint8_t handle, ft_uint16_t width, ft_uint16_t height)
{
	Ft_Esd_Dl_BITMAP_HANDLE(handle);
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BITMAP_SIZE(NEAREST, BORDER, BORDER, width & 0x1ff, height & 0x1ff));
#ifdef FT_81X_ENABLE
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BITMAP_SIZE_H(width >> 9, height >> 9));
#endif
	Ft_Esd_BitmapHandleResized[handle] = 1;
}

void Ft_Esd_Dl_Bitmap_WidthHeight_BILINEAR(ft_uint8_t handle, ft_uint16_t width, ft_uint16_t height)
{
	Ft_Esd_Dl_BITMAP_HANDLE(handle);
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BITMAP_SIZE(BILINEAR, BORDER, BORDER, width & 0x1ff, height & 0x1ff));
#ifdef FT_81X_ENABLE
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BITMAP_SIZE_H(width >> 9, height >> 9));
#endif
	Ft_Esd_BitmapHandleResized[handle] = 1;
}

void Ft_Esd_Dl_Bitmap_WidthHeightReset(ft_uint8_t handle)
{
	if (Ft_Esd_BitmapHandleResized[handle])
	{
		Ft_Esd_BitmapInfo *bitmapInfo = Ft_Esd_BitmapHandleInfo[handle];
		Ft_Esd_Dl_Bitmap_WidthHeight(handle, bitmapInfo->Width, bitmapInfo->Height);
		Ft_Esd_BitmapHandleResized[handle] = 0;
	}
}

Ft_Esd_Rect16 Ft_Esd_Dl_Scissor_Set(Ft_Esd_Rect16 rect)
{
	Ft_Esd_Rect16 state = Ft_Esd_ScissorRect;
	Ft_Esd_Dl_Scissor_Adjust(rect, state);
	return state;
}

void Ft_Esd_Dl_Scissor_Adjust(Ft_Esd_Rect16 rect, Ft_Esd_Rect16 state)
{
	if (state.X > rect.X)
	{
		rect.Width -= state.X - rect.X;
		rect.X = state.X;
	}
	if (state.Y > rect.Y)
	{
		rect.Height -= state.Y = rect.Y;
		rect.Y = state.Y;
	}
	if (state.Width < rect.Width)
	{
		rect.Width = state.Width;
	}
	if (state.Height < rect.Height)
	{
		rect.Height = state.Height;
	}
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, SCISSOR_XY(rect.X, rect.Y));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, SCISSOR_SIZE(rect.Width, rect.Height));
	Ft_Esd_ScissorRect = rect;
}

void Ft_Esd_Dl_Scissor_Reset(Ft_Esd_Rect16 state)
{
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, SCISSOR_XY(state.X, state.Y));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, SCISSOR_SIZE(state.Width, state.Height));
	Ft_Esd_ScissorRect = state;
}

/* end of file */
