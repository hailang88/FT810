/**
* This source code ("the Software") is provided by Bridgetek Pte Ltd
* ("Bridgetek") subject to the licence terms set out
*   http://brtchip.com/BRTSourceCodeLicenseAgreement/ ("the Licence Terms").
* You must read the Licence Terms before downloading or using the Software.
* By installing or using the Software you agree to the Licence Terms. If you
* do not agree to the Licence Terms then do not download or use the Software.
*
* Without prejudice to the Licence Terms, here is a summary of some of the key
* terms of the Licence Terms (and in the event of any conflict between this
* summary and the Licence Terms then the text of the Licence Terms will
* prevail).
*
* The Software is provided "as is".
* There are no warranties (or similar) in relation to the quality of the
* Software. You use it at your own risk.
* The Software should not be used in, or for, any medical device, system or
* appliance. There are exclusions of Bridgetek liability for certain types of loss
* such as: special loss or damage; incidental loss or damage; indirect or
* consequential loss or damage; loss of income; loss of business; loss of
* profits; loss of revenue; loss of contracts; business interruption; loss of
* the use of money or anticipated savings; loss of information; loss of
* opportunity; loss of goodwill or reputation; and/or loss of, damage to or
* corruption of data.
* There is a monetary cap on Bridgetek's liability.
* The Software may have subsequently been amended by another user and then
* distributed by that other user ("Adapted Software").  If so that user may
* have additional licence terms that apply to those amendments. However, Bridgetek
* has no liability in relation to those amendments.
*/

#include <FT_Platform.h>
#include "Ft_Esd.h"
#include "Ft_Esd_GpuAlloc.h"

 extern   void  Delay_ms(unsigned int  t);
//
// Static
//
static Ft_Gpu_Hal_Context_t s_Host;
static Ft_Esd_GpuAlloc s_GAlloc;


//
// Globals
//
Ft_Gpu_Hal_Context_t *Ft_Esd_Host = 0; // Pointer to s_Host
Ft_Esd_GpuAlloc *Ft_Esd_GAlloc = 0; // Pointer to s_GAlloc
ft_uint32_t Ft_Esd_Millis = 0;  // Time in milliseconds for current frame
ft_uint32_t Ft_Esd_DeltaMs = 0; // Delta time in milliseconds between frames
ft_uint32_t Ft_Esd_Frame = 0;   // Number of times Render has been called
ft_rgb32_t Ft_Esd_ClearColor = 0x212121; // Screen clear color
ft_uint8_t Ft_Esd_LoopState = ESD_LOOPSTATE_NONE;

/*A function to get milliseconds for current frame*/
ESD_FUNCTION(Ft_Esd_GetMillis, Type = ft_uint32_t, DisplayName = "Get Milliseconds", Category = EsdUtilities)
ft_uint32_t Ft_Esd_GetMillis() { return Ft_Esd_Millis; }

/* A function to get the difference in milliseconds since last frame Update call */
ESD_FUNCTION(Ft_Esd_GetDeltaMs, Type = ft_uint32_t, DisplayName = "Get Delta Ms", Category = EsdUtilities)
ft_uint32_t Ft_Esd_GetDeltaMs() { return Ft_Esd_DeltaMs; }

/* A function to get the global HAL context data structure*/
ESD_FUNCTION(Ft_Esd_GetHost, Type = Ft_Gpu_Hal_Context_t *, DisplayName = "Get EVE Host", Category = EsdUtilities)
Ft_Gpu_Hal_Context_t *Ft_Esd_GetHost() { return Ft_Esd_Host; }

ft_uint16_t Ft_Esd_FontHeight[35] = { 0 }; // Font heights of currently set bitmaps

/* Global variables for display resolution to support various display panels */
/* Default is WQVGA - 480x272 */
ft_int16_t FT_DispWidth = 480;
ft_int16_t FT_DispHeight = 272;
ft_int16_t FT_DispHCycle = 548;
ft_int16_t FT_DispHOffset = 43;
ft_int16_t FT_DispHSync0 = 0;
ft_int16_t FT_DispHSync1 = 41;
ft_int16_t FT_DispVCycle = 292;
ft_int16_t FT_DispVOffset = 12;
ft_int16_t FT_DispVSync0 = 0;
ft_int16_t FT_DispVSync1 = 10;
ft_uint8_t FT_DispPCLK = 5;
ft_char8_t FT_DispSwizzle = 0;
ft_char8_t FT_DispPCLKPol = 1;
ft_char8_t FT_DispCSpread = 1;
ft_char8_t FT_DispDither = 1;

#ifdef ESD_SIMULATION
int Ft_Esd_DesignerMode = 0;
#endif

/* Initial boot up display list */
const ft_uint32_t FT_DLCODE_BOOTUP[] = {
	CLEAR_COLOR_RGB(0, 0, 0),
	CLEAR(1, 1, 1),
//	BITMAP_HANDLE(31),
//	BEGIN(BITMAPS),
//	VERTEX2II(6, 0, 31, 'E'),
//	VERTEX2II(29, 0, 31, 'S'),
//	VERTEX2II(55, 0, 31, 'D'),
//	VERTEX2II(83, 0, 31, '3'),
//	BITMAP_HANDLE(28),
//	BEGIN(BITMAPS),
//	VERTEX2II(7, 43, 28, 'H'),
//	VERTEX2II(22, 43, 28, 'e'),
//	VERTEX2II(33, 43, 28, 'l'),
//	VERTEX2II(39, 43, 28, 'l'),
//	VERTEX2II(45, 43, 28, 'o'),
	DISPLAY(),
};

//#define FT_WELCOME_MESSAGE "Copyright (C) Bridgetek Pte Ltd.\r\n"

#if defined(FT900_PLATFORM) && !defined(ESD_SIMULATION)
ft_void_t FT900_Config()
{
	sys_enable(sys_device_uart0);
	gpio_function(48, pad_uart0_txd); /* UART0 TXD */
	gpio_function(49, pad_uart0_rxd); /* UART0 RXD */
	uart_open(UART0,     /* Device */
		1,      /* Prescaler = 1 */
		UART_DIVIDER_115200_BAUD,  /* Divider = 1302 */
		uart_data_bits_8,   /* No. Data Bits */
		uart_parity_none,   /* Parity */
		uart_stop_bits_1);  /* No. Stop Bits */

	/* Print out a welcome message... */
	uart_puts(UART0, FT_WELCOME_MESSAGE);

#if (defined(ENABLE_ILI9488_HVGA_PORTRAIT) || defined(ENABLE_KD2401_HVGA_PORTRAIT))
	/* asign all the respective pins to gpio and set them to default values */
	gpio_function(34, pad_gpio34);
	gpio_dir(34, pad_dir_output);
	gpio_write(34, 1);

	gpio_function(27, pad_gpio27);
	gpio_dir(27, pad_dir_output);
	gpio_write(27, 1);

	gpio_function(29, pad_gpio29);
	gpio_dir(29, pad_dir_output);
	gpio_write(29, 1);

	gpio_function(33, pad_gpio33);
	gpio_dir(33, pad_dir_output);
	gpio_write(33, 1);


	gpio_function(30, pad_gpio30);
	gpio_dir(30, pad_dir_output);
	gpio_write(30, 1);

	gpio_function(28, pad_gpio28);
	gpio_dir(28, pad_dir_output);
	gpio_write(28, 1);


	gpio_function(43, pad_gpio43);
	gpio_dir(43, pad_dir_output);
	gpio_write(43, 1);
	gpio_write(34, 1);
	gpio_write(28, 1);
	gpio_write(43, 1);
	gpio_write(33, 1);
	gpio_write(33, 1);

#endif

	/* useful for timer */
	ft_millis_init();
	interrupt_enable_globally();
	//ESD_print("ft900 config done \n");}
}
#endif

ft_void_t FT800_BootupConfig()
{
	Ft_Gpu_Hal_Powercycle(&s_Host, FT_TRUE);

	/* Set the clk to external clock */
#if (!defined(ME800A_HV35R) && !defined(ME810A_HV35R) && !defined(ME812A_WH50R))
	Ft_Gpu_HostCommand(&s_Host, FT_GPU_EXTERNAL_OSC);
	Ft_Gpu_Hal_Sleep(10);
#endif

	/* Access address 0 to wake up the FT800 */
	Ft_Gpu_HostCommand(&s_Host, FT_GPU_ACTIVE_M);
	Ft_Gpu_Hal_Sleep(300);

#if !(defined(MSVC_FT800EMU) || defined(ESD_SIMULATION))
#if defined(FT_811_ENABLE) || defined(FT_813_ENABLE)
	/* Download new firmware to fix pen up issue */
	Ft_Gpu_DownloadJ1Firmware(&s_Host);
	Ft_Gpu_Hal_Sleep(100);
#endif
#endif	

	; {
		ft_uint8_t chipid;
		//Read Register ID to check if FT800 is ready.
		chipid = Ft_Gpu_Hal_Rd8(&s_Host, REG_ID);
		while (chipid != 0x7C)
		{
			chipid = Ft_Gpu_Hal_Rd8(&s_Host, REG_ID);
			ESD_print("VC1 register ID after wake up %x\n", chipid);
			ft_delay(100);
		}
#if defined(MSVC_PLATFORM) || defined (FT900_PLATFORM) || defined(ESD_SIMULATION)
		ESD_print("VC1 register ID after wake up %x\n", chipid);
#endif
	}

	/* Configuration of LCD display */
#ifdef DISPLAY_RESOLUTION_QVGA
	/* Values specific to QVGA LCD display */
	FT_DispWidth = 320;
	FT_DispHeight = 240;
	FT_DispHCycle =  408;
	FT_DispHOffset = 70;
	FT_DispHSync0 = 0;
	FT_DispHSync1 = 10;
	FT_DispVCycle = 263;
	FT_DispVOffset = 13;
	FT_DispVSync0 = 0;
	FT_DispVSync1 = 2;
	FT_DispPCLK = 8;
	FT_DispSwizzle = 2;
	FT_DispPCLKPol = 0;
	FT_DispCSpread = 1;
	FT_DispDither = 1;
#endif

#ifdef DISPLAY_RESOLUTION_WVGA
	/* Values specific to QVGA LCD display */
	FT_DispWidth = 800;
	FT_DispHeight = 480;
	FT_DispHCycle =  928;
	FT_DispHOffset = 88;
	FT_DispHSync0 = 0;
	FT_DispHSync1 = 48;
	FT_DispVCycle = 525;
	FT_DispVOffset = 32;
	FT_DispVSync0 = 0;
	FT_DispVSync1 = 3;
	FT_DispPCLK = 2;
	FT_DispSwizzle = 0;
	FT_DispPCLKPol = 1;
	FT_DispCSpread = 0;
	FT_DispDither = 1;
#endif

#ifdef DISPLAY_RESOLUTION_HVGA_PORTRAIT
	/* Values specific to HVGA LCD display */
	FT_DispWidth = 320;
	FT_DispHeight = 480;
	FT_DispHCycle =  400;
	FT_DispHOffset = 40;
	FT_DispHSync0 = 0;
	FT_DispHSync1 = 10;
	FT_DispVCycle = 500;
	FT_DispVOffset = 10;
	FT_DispVSync0 = 0;
	FT_DispVSync1 = 5;
	FT_DispPCLK = 4;
#ifdef ENABLE_ILI9488_HVGA_PORTRAIT
	FT_DispSwizzle = 2;
	FT_DispPCLKPol = 1;
#endif
#ifdef ENABLE_KD2401_HVGA_PORTRAIT
	FT_DispSwizzle = 0;
	FT_DispPCLKPol = 0;
	FT_DispPCLK = 5;
#endif
	FT_DispCSpread = 1;
	FT_DispDither = 1;
#ifdef ME810A_HV35R
	FT_DispPCLK = 5;
#endif
#endif

#if (defined(ME800A_HV35R) || defined(ME810A_HV35R))
	/* After recognizing the type of chip, perform the trimming if necessary */
	Ft_Gpu_ClockTrimming(&s_Host, LOW_FREQ_BOUND);
#endif

	Ft_Gpu_Hal_Wr16(&s_Host, REG_HCYCLE, FT_DispHCycle);
	Ft_Gpu_Hal_Wr16(&s_Host, REG_HOFFSET, FT_DispHOffset);
	Ft_Gpu_Hal_Wr16(&s_Host, REG_HSYNC0, FT_DispHSync0);
	Ft_Gpu_Hal_Wr16(&s_Host, REG_HSYNC1, FT_DispHSync1);
	Ft_Gpu_Hal_Wr16(&s_Host, REG_VCYCLE, FT_DispVCycle);
	Ft_Gpu_Hal_Wr16(&s_Host, REG_VOFFSET, FT_DispVOffset);
	Ft_Gpu_Hal_Wr16(&s_Host, REG_VSYNC0, FT_DispVSync0);
	Ft_Gpu_Hal_Wr16(&s_Host, REG_VSYNC1, FT_DispVSync1);
	Ft_Gpu_Hal_Wr8(&s_Host, REG_SWIZZLE, FT_DispSwizzle);
	Ft_Gpu_Hal_Wr8(&s_Host, REG_PCLK_POL, FT_DispPCLKPol);
	Ft_Gpu_Hal_Wr16(&s_Host, REG_HSIZE, FT_DispWidth);
	Ft_Gpu_Hal_Wr16(&s_Host, REG_VSIZE, FT_DispHeight);
	Ft_Gpu_Hal_Wr16(&s_Host, REG_CSPREAD, FT_DispCSpread);
	Ft_Gpu_Hal_Wr16(&s_Host, REG_DITHER, FT_DispDither);

#if (defined(FT_800_ENABLE) || defined(FT_810_ENABLE) ||defined(FT_812_ENABLE))
	/* Touch configuration - configure the resistance value to 1200 - this value is specific to customer requirement and derived by experiment */
	Ft_Gpu_Hal_Wr16(&s_Host, REG_TOUCH_RZTHRESH, RESISTANCE_THRESHOLD);
#endif

#if defined(FT_81X_ENABLE)
    Ft_Gpu_Hal_Wr16(&s_Host, REG_GPIOX_DIR, 0xffff);
    Ft_Gpu_Hal_Wr16(&s_Host, REG_GPIOX, 0xffff);
#else
    Ft_Gpu_Hal_Wr8(&s_Host, REG_GPIO_DIR,0xff);
    Ft_Gpu_Hal_Wr8(&s_Host, REG_GPIO,0xff);
#endif

	Ft_Gpu_Hal_WrMem(&s_Host, RAM_DL, (ft_uint8_t *)FT_DLCODE_BOOTUP, sizeof(FT_DLCODE_BOOTUP));
	Ft_Gpu_Hal_Wr8(&s_Host, REG_DLSWAP, DLSWAP_FRAME);

	Ft_Gpu_Hal_Wr8(&s_Host, REG_PCLK, FT_DispPCLK);//after this display is visible on the LCD

#if (defined(ENABLE_ILI9488_HVGA_PORTRAIT) || defined(ENABLE_KD2401_HVGA_PORTRAIT))
	/* to cross check reset pin */
	Ft_Gpu_Hal_Wr8(&s_Host, REG_GPIO, 0xff);
	ft_delay(120);
	Ft_Gpu_Hal_Wr8(&s_Host, REG_GPIO, 0x7f);
	ft_delay(120);
	Ft_Gpu_Hal_Wr8(&s_Host, REG_GPIO,0xff);
#endif

#ifndef ESD_SIMULATION
    
#ifdef ENABLE_ILI9488_HVGA_PORTRAIT
	ILI9488_Bootup();
	ESD_print("after ILI9488 bootup \n");
#endif

#ifdef ENABLE_KD2401_HVGA_PORTRAIT
	KD2401_Bootup();
	ESD_print("after KD2401 bootup \n");
#endif

	/* Reconfigure the SPI */
#ifdef FT900_PLATFORM
	//spi
	// Initialize SPIM HW
	sys_enable(sys_device_spi_master);
	gpio_function(27, pad_spim_sck); /* GPIO27 to SPIM_CLK */
	gpio_function(28, pad_spim_ss0); /* GPIO28 as CS */
	gpio_function(29, pad_spim_mosi); /* GPIO29 to SPIM_MOSI */
	gpio_function(30, pad_spim_miso); /* GPIO30 to SPIM_MISO */

	gpio_write(28, 1);
	spi_init(SPIM, spi_dir_master, spi_mode_0, 4);
#endif

#endif /*ifndef ESD_SIMULATION*/




	/* make the spi to quad mode - addition 2 bytes for silicon */
#ifdef FT_81X_ENABLE
	/* api to set quad and numbe of dummy bytes */
#ifdef ENABLE_SPI_QUAD
	Ft_Gpu_Hal_SetSPI(&s_Host,FT_GPU_SPI_QUAD_CHANNEL,FT_GPU_SPI_TWODUMMY);
#elif ENABLE_SPI_DUAL
	Ft_Gpu_Hal_SetSPI(&s_Host,FT_GPU_SPI_DUAL_CHANNEL,FT_GPU_SPI_TWODUMMY);
#else
	Ft_Gpu_Hal_SetSPI(&s_Host, FT_GPU_SPI_SINGLE_CHANNEL, FT_GPU_SPI_ONEDUMMY);
#endif

#endif



#if defined(FT900_PLATFORM) && !defined(ESD_SIMULATION)
	/* Change clock frequency to 25mhz */
	spi_init(SPIM, spi_dir_master, spi_mode_0, 4);

#if (defined(ENABLE_SPI_QUAD))
	/* Initialize IO2 and IO3 pad/pin for dual and quad settings */
	gpio_function(31, pad_spim_io2);
	gpio_function(32, pad_spim_io3);
	gpio_write(31, 1);
	gpio_write(32, 1);
#endif
	/* Enable FIFO of QSPI */
	spi_option(SPIM, spi_option_fifo_size, 64);
	spi_option(SPIM, spi_option_fifo, 1);
	spi_option(SPIM, spi_option_fifo_receive_trigger, 1);
#endif

#ifdef ENABLE_SPI_QUAD
#if defined(FT900_PLATFORM) && !defined(ESD_SIMULATION)
	spi_option(SPIM,spi_option_bus_width,4);
#endif
#elif ENABLE_SPI_DUAL
#if defined(FT900_PLATFORM) && !defined(ESD_SIMULATION)
	spi_option(SPIM,spi_option_bus_width,2);
#endif
#else
#if defined(FT900_PLATFORM) && !defined(ESD_SIMULATION)
	spi_option(SPIM, spi_option_bus_width, 1);
#endif


#endif

	s_Host.ft_cmd_fifo_wp = Ft_Gpu_Hal_Rd16(&s_Host, REG_CMD_WRITE);
}

#if defined(FT900_PLATFORM) && !defined(ESD_SIMULATION)
ft_void_t FT900_InitSDCard()
{
	sys_enable(sys_device_sd_card);
	sdhost_init();

#define GPIO_SD_CLK  (19)
#define GPIO_SD_CMD  (20)
#define GPIO_SD_DAT3 (21)
#define GPIO_SD_DAT2 (22)
#define GPIO_SD_DAT1 (23)
#define GPIO_SD_DAT0 (24)
#define GPIO_SD_CD   (25)
#define GPIO_SD_WP   (26)

	gpio_function(GPIO_SD_CLK, pad_sd_clk); gpio_pull(GPIO_SD_CLK, pad_pull_none); // pad_pull_none
	gpio_function(GPIO_SD_CMD, pad_sd_cmd); gpio_pull(GPIO_SD_CMD, pad_pull_pullup);
	gpio_function(GPIO_SD_DAT3, pad_sd_data3); gpio_pull(GPIO_SD_DAT3, pad_pull_pullup);
	gpio_function(GPIO_SD_DAT2, pad_sd_data2); gpio_pull(GPIO_SD_DAT2, pad_pull_pullup);
	gpio_function(GPIO_SD_DAT1, pad_sd_data1); gpio_pull(GPIO_SD_DAT1, pad_pull_pullup);
	gpio_function(GPIO_SD_DAT0, pad_sd_data0); gpio_pull(GPIO_SD_DAT0, pad_pull_pullup);
	gpio_function(GPIO_SD_CD, pad_sd_cd); gpio_pull(GPIO_SD_CD, pad_pull_pullup);
	gpio_function(GPIO_SD_WP, pad_sd_wp); gpio_pull(GPIO_SD_WP, pad_pull_pullup);

}
#endif

/* API to demonstrate calibrate widget/functionality */
ft_void_t App_CoPro_Widget_Calibrate()
{
	ft_uint32_t NumBytesGen = 0, TransMatrix[6];
	ft_uint16_t CurrWriteOffset = 0;
	Ft_Gpu_CoCmd_Dlstart(&s_Host);
	Ft_Gpu_Hal_WrCmd32(&s_Host, CLEAR_COLOR_RGB(64, 64, 64));
	Ft_Gpu_Hal_WrCmd32(&s_Host, CLEAR(1, 1, 1));
	Ft_Gpu_Hal_WrCmd32(&s_Host, COLOR_RGB(0xff, 0xff, 0xff));
	/* Draw number at 0,0 location */
	//Ft_App_WrCoCmd_Buffer(&s_Host, COLOR_A(30));
	Ft_Gpu_CoCmd_Text(&s_Host, (FT_DispWidth / 2), (FT_DispHeight / 2), 27, OPT_CENTER, "Please Tap on the dot");
#if defined(FT_801_ENABLE) || defined(FT_811_ENABLE) || defined(FT_813_ENABLE)
	Ft_Gpu_Hal_Wr8(&s_Host, REG_CTOUCH_EXTENDED, CTOUCH_MODE_COMPATIBILITY);
#endif
	Ft_Gpu_CoCmd_Calibrate(&s_Host, 0);
	/* Wait till coprocessor completes the operation */
	Ft_Gpu_Hal_WaitCmdfifo_empty(&s_Host);
	/* Print the configured values */
	Ft_Gpu_Hal_RdMem(&s_Host, REG_TOUCH_TRANSFORM_A, (ft_uint8_t *)TransMatrix, 4 * 6); //read all the 6 coefficients
#ifdef MSVC_PLATFORM
	ESD_print("Touch screen transform values are A 0x%x,B 0x%x,C 0x%x,D 0x%x,E 0x%x, F 0x%x",
		TransMatrix[0], TransMatrix[1], TransMatrix[2], TransMatrix[3], TransMatrix[4], TransMatrix[5]);
#endif
}

// TODO: Update Ft_Esd_FontHeight on CMD_ROMFONT
// TODO: Update Ft_Esd_FontHeight on CMD_SETFONT
ft_void_t Ft_Esd_InitFontHeight()
{
	ft_uint32_t ft = Ft_Gpu_Hal_Rd32(&s_Host, ROMFONT_TABLEADDRESS);
	for (int i = 0; i < 19; ++i)
	{
		ft_uint32_t addr = ft + (FT_GPU_FONT_TABLE_SIZE * i) + (ft_uint32_t)(uintptr_t)(&(((FT_Gpu_Fonts_t *)(void *)0)->FontHeightInPixels));
		Ft_Esd_FontHeight[16 + i] = Ft_Gpu_Hal_Rd16(&s_Host, addr);
	}
}

ft_void_t setup()
{

}

// Ft_Esd_MainLoop
ft_void_t Ft_Esd_MainLoop();


#if defined(ARDUINO_PLATFORM) || defined(MSVC_FT800EMU)
ft_void_t loop()
#endif
{



	Ft_Gpu_HalInit_t halinit;

	halinit.TotalChannelNum = 1;


	Ft_Gpu_Hal_Init(&halinit);
	s_Host.hal_config.channel_no = 0;
	s_Host.hal_config.pdn_pin_no = FT800_PD_N;
	s_Host.hal_config.spi_cs_pin_no = FT800_SEL_PIN;

	Ft_Gpu_Hal_Open(&s_Host);

	//ESD_print("Ft_Gpu_Hal_Open done \n");
	Ft_Esd_Host = &s_Host;

	FT800_BootupConfig();

	App_CoPro_Widget_Calibrate();


	Ft_Esd_GAlloc = &s_GAlloc;
	Ft_Esd_GpuAlloc_Reset(&s_GAlloc);

	Ft_Esd_InitFontHeight();

	Ft_Esd_MainLoop();

	Ft_Gpu_Hal_Close(&s_Host);
	Ft_Gpu_Hal_DeInit();
	Ft_Esd_Host = 0;
}

ft_uint32_t Ft_Esd_GAlloc_GetTotalUsed(Ft_Esd_GpuAlloc *ga)
{
	if (!Ft_Esd_GAlloc) return 0;
	return Ft_Esd_GpuAlloc_GetTotalUsed(Ft_Esd_GAlloc);
}

ft_uint32_t Ft_Esd_GAlloc_GetTotal(Ft_Esd_GpuAlloc *ga)
{
	if (!Ft_Esd_GAlloc) return 0;
	return Ft_Esd_GpuAlloc_GetTotal(Ft_Esd_GAlloc);
}

/* Nothing beyond this */
