/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * $Revision: 3 $
 * $Date: 14/01/28 11:45a $
 * @brief    Template project for M051 series MCU
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
//#include <cmsis_os.h>
#include "M051Series.h"
//#include "M0519.h"
//#include "TFT.h"
#include "App.h"
extern  ft_void_t loop();
//extern  void TFT_TASK(void const *argument);

//osThreadId  main_ID,TFT_ID;
//osThreadDef(TFT_TASK, osPriorityNormal, 1, 0);



/*---------------------------------------------------------------------------------------------------------*/
/* Define functions prototype                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void);
void  Delay_ms(unsigned int  t)
{
    unsigned int  i;
    for (i = 0; i < t; i++)
    {
        CLK_SysTickDelay(1000);
    }

}

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();
    /* Enable external 12MHz XTAL */
    CLK_EnableXtalRC(CLK_PWRCON_XTL12M_EN_Msk);

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_XTL12M_STB_Msk);

    /* Switch HCLK clock source to HXT and HCLK source divide 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HXT, CLK_CLKDIV_HCLK(1));
    CLK_SetCoreClock(50000000);
    /* Select HXT as the clock source of UART0 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART_S_HXT, CLK_CLKDIV_UART(1));

    /* Select HCLK as the clock source of SPI0 */
    CLK_SetModuleClock(SPI0_MODULE, CLK_CLKSEL1_SPI0_S_HCLK, MODULE_NoMsk);

    /* Enable UART peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);
    /* Enable SPI0 peripheral clock */
    CLK_EnableModuleClock(SPI0_MODULE);


    /* Set P3 multi-function pins for UART0 RXD and TXD  */
    SYS->P3_MFP = SYS_MFP_P30_RXD0 | SYS_MFP_P31_TXD0;
    /* Setup SPI0 multi-function pins */
    //  SYS->P1_MFP = SYS_MFP_P14_SPISS0 | SYS_MFP_P15_MOSI_0 | SYS_MFP_P16_MISO_0 | SYS_MFP_P17_SPICLK0;
    SYS->P1_MFP = SYS_MFP_P15_MOSI_0 | SYS_MFP_P16_MISO_0 | SYS_MFP_P17_SPICLK0;
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and cyclesPerUs automatically. */
    SystemCoreClockUpdate();
    /* Lock protected registers */
    SYS_LockReg();
    GPIO_SetMode(P3, BIT5, GPIO_PMD_OPEN_DRAIN);
    GPIO_SetMode(P1, BIT4, GPIO_PMD_OUTPUT);

}
void SPI_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init SPI                                                                                                */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Configure as a master, clock idle low, 32-bit transaction, drive output on falling clock edge and latch input on rising edge. */
    /* Set IP clock divider. SPI clock rate = 2MHz */
    SPI_Open(SPI0, SPI_MASTER, SPI_MODE_0, 8, 10000000);

    /* Enable the automatic hardware slave select function. Select the SS pin and configure as low-active. */
    // SPI_EnableAutoSS(SPI0, SPI_SS, SPI_SS_ACTIVE_LOW);
}









int main()
{
    SYS_Init();
// osKernelInitialize ();
    //   TFT_ID = osThreadCreate(osThread(TFT_TASK), NULL);
    //SYS_ResetModule(UART0_RST);
    // UART_Open(UART0, 115200);
    SPI_Init();
    //  APP_Init();

    //  osKernelStart ();
    loop();
    while(1)
    {
        //		APP_Calibrate();
        //	  APP_FlashingDot();
        //    Delay_ms(10000);
        //    APP_VertexTranslate();
        //		Delay_ms(10000);
        //    APP_Text();
        //		Delay_ms(10000);
//     APP_ConvertedBitmap();
        //		Delay_ms(10000);
        //   APP_SliderandButton();
        //	Delay_ms(10000);
        //  APP_SnapShot2();
        //	Delay_ms(10000);
        //  APP_DigitsFont();


//			EVE_MemWrite8(REG_VOL_SOUND, 0xFF);
//			EVE_MemWrite16(REG_SOUND,(0<<8)|(ch++));
//			EVE_MemWrite8(REG_PLAY,1);
//			Sound_status = EVE_MemRead8(REG_PLAY);
//			Delay_ms(1000);
//		   EVE_MemWrite16(REG_SOUND,0x0);// ???????????
//       EVE_MemWrite8(REG_PLAY,1);// ????
//       Sound_status = EVE_MemRead8(REG_PLAY);// 1-??????, 0-??????
//			 Delay_ms(1000);
//
//
//dli =0;
//dl(CLEAR(1,1,1));//
//EVE_MemWrite32(RAM_DL +4, BEGIN(BITMAPS));//??????
//EVE_MemWrite32(RAM_DL +8, VERTEX2II(220,110,31,'F'));// ??31?ascii F
//EVE_MemWrite32(RAM_DL +12, VERTEX2II(244,110,31,'T'));// ascii T
//EVE_MemWrite32(RAM_DL +16, VERTEX2II(270,110,31,'D'));// ascii D
//EVE_MemWrite32(RAM_DL +20, VERTEX2II(299,110,31,'I'));// ascii I
//EVE_MemWrite32(RAM_DL +24, END());
//EVE_MemWrite32(RAM_DL +28, COLOR_RGB(160,22,22));// ???????
//EVE_MemWrite32(RAM_DL +32, POINT_SIZE(320));//??????????20??(20*16)
//EVE_MemWrite32(RAM_DL +36, BEGIN(FTPOINTS));//?????
//EVE_MemWrite32(RAM_DL +40, VERTEX2II(192,133,0,0));//??
//EVE_MemWrite32(RAM_DL +44, END());
//EVE_MemWrite32(RAM_DL +48, DISPLAY());//????
        /*   */
//dli =0;
//dl(CLEAR(1,1,1));//
//dl( BEGIN(FTPOINTS) );
//dl( VERTEX2II(ch, 5, 0, 0) );
//dl( VERTEX2II(110, 15, 0, 0) );
//dl( BEGIN(LINES) );
//dl( VERTEX2II(50, 45, 0, 0) );
//dl( VERTEX2II(110, 55, 0, 0) );
//dl( BEGIN(BITMAPS) );
//dl( VERTEX2II(50, 65, 31, 0x45) );
//dl( VERTEX2II(110, 75, 31, 0x46) );
//dl(END());
//dl(DISPLAY());
//dl( STENCIL_OP(INCR, INCR) );
//dl( POINT_SIZE(760) );
//dl( BEGIN(FTPOINTS) );
//dl( VERTEX2II(50, 60, 0, 0) );
//dl( VERTEX2II(110, 60, 0, 0) );
//dl( STENCIL_FUNC(EQUAL, 2, 255) );
//dl( COLOR_RGB(100, 0, 0) );
//dl( VERTEX2II(80, 60, 0, 0) );
//dl(END());
//dl(DISPLAY());
        Delay_ms(1000);

    }

}


