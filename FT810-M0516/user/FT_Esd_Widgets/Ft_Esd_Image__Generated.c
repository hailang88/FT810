/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_Image
C Source
*/

#include "Ft_Esd_Image.h"


extern void Ft_Esd_Noop(void *context);
Ft_Esd_BitmapCell Ft_Esd_Image_BitmapCell__Default(void *context) { return (Ft_Esd_BitmapCell){ 0 }; }


static Ft_Esd_WidgetSlots s_Ft_Esd_Image__Slots = {
	(void(*)(void *))Ft_Esd_Widget_Initialize,
	(void(*)(void *))Ft_Esd_Widget_Start,
	(void(*)(void *))Ft_Esd_Widget_Enable,
	(void(*)(void *))Ft_Esd_Widget_Update,
	(void(*)(void *))Ft_Esd_Image_Render,
	(void(*)(void *))Ft_Esd_Widget_Idle,
	(void(*)(void *))Ft_Esd_Widget_Disable,
	(void(*)(void *))Ft_Esd_Widget_End,
};


void Ft_Esd_Image__Initializer(Ft_Esd_Image *context)
{
	Ft_Esd_Widget__Initializer((Ft_Esd_Widget *)context);
	context->Widget.ClassId = Ft_Esd_Image_CLASSID;
	context->Widget.Slots = &s_Ft_Esd_Image__Slots;
	context->Widget.LocalX = 70;
	context->Widget.LocalY = 92;
	context->Widget.LocalWidth = 100;
	context->Widget.LocalHeight = 100;
	context->Color = 0xffffffffUL;
	context->BitmapCell = Ft_Esd_Image_BitmapCell__Default;
	context->Align = ESD_ALIGN_TOPLEFT;
	context->Scaling = ESD_SCALING_ORIGINAL;
	context->AutoResize = ESD_AUTORESIZE_BOTH;
	context->ScaleX = (1L * (1L << 16) + 0x0L);
	context->ScaleY = (1L * (1L << 16) + 0x0L);
}

void Ft_Esd_Image_Render_Bitmap(Ft_Esd_Image *context);

void Ft_Esd_Image_Render(Ft_Esd_Image *context)
{
	void *owner = context->Owner;
	Ft_Esd_Image_Render_Bitmap(context);
	Ft_Esd_Widget_Render((Ft_Esd_Widget *)context); 
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	Ft_Esd_Image Instance;
	Ft_Esd_BitmapCell BitmapCell;
} Ft_Esd_Image__ESD;

Ft_Esd_BitmapCell Ft_Esd_Image__Get_BitmapCell__ESD(void *context) { return ((Ft_Esd_Image__ESD *)context)->BitmapCell; }
void Ft_Esd_Image__Set_BitmapCell__ESD(void *context, Ft_Esd_BitmapCell value) { ((Ft_Esd_Image__ESD *)context)->BitmapCell = value; }

void *Ft_Esd_Image__Create__ESD()
{
	Ft_Esd_Image__ESD *context = (Ft_Esd_Image__ESD *)malloc(sizeof(Ft_Esd_Image__ESD));
	Ft_Esd_Image__Initializer(&context->Instance);
	context->Instance.Owner = context;
	context->BitmapCell = (Ft_Esd_BitmapCell){ 0 };
	context->Instance.BitmapCell = Ft_Esd_Image__Get_BitmapCell__ESD;
	return context;
}

void Ft_Esd_Image__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_Image__Set_Color__ESD(void *context, ft_argb32_t value) { ((Ft_Esd_Image__ESD *)context)->Instance.Color = value; }
void Ft_Esd_Image__Set_Align__ESD(void *context, ft_uint8_t value) { ((Ft_Esd_Image__ESD *)context)->Instance.Align = value; }
void Ft_Esd_Image__Set_Scaling__ESD(void *context, ft_uint8_t value) { ((Ft_Esd_Image__ESD *)context)->Instance.Scaling = value; }
void Ft_Esd_Image__Set_AutoResize__ESD(void *context, ft_uint8_t value) { ((Ft_Esd_Image__ESD *)context)->Instance.AutoResize = value; }
void Ft_Esd_Image__Set_ScaleX__ESD(void *context, ft_int32_f16_t value) { ((Ft_Esd_Image__ESD *)context)->Instance.ScaleX = value; }
void Ft_Esd_Image__Set_ScaleY__ESD(void *context, ft_int32_f16_t value) { ((Ft_Esd_Image__ESD *)context)->Instance.ScaleY = value; }

#endif /* ESD_SIMULATION */

/* end of file */
