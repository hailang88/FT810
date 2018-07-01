#include <cmsis_os.h>
//#include "main.h"
#include "TFT.h"
//#include "EVE_RGB565.h"
//#include "DIGITfont.h"
#include "App.h"
 extern  ft_void_t loop();

void TFT_TASK(void const *argument)
{
	
	//Ft_Esd_MainLoop();
	 loop();
	//  Ft_Main__Start();
//	APP_Init();
//	APP_Calibrate();
//	TOUCH_TRANSFORM[0]=EVE_MemRead32(REG_TOUCH_TRANSFORM_A); 
//	TOUCH_TRANSFORM[1]=EVE_MemRead32(REG_TOUCH_TRANSFORM_B); 
//	TOUCH_TRANSFORM[2]=EVE_MemRead32(REG_TOUCH_TRANSFORM_C); 
//	TOUCH_TRANSFORM[3]=EVE_MemRead32(REG_TOUCH_TRANSFORM_D); 
//	TOUCH_TRANSFORM[4]=EVE_MemRead32(REG_TOUCH_TRANSFORM_E); 
//	TOUCH_TRANSFORM[5]=EVE_MemRead32(REG_TOUCH_TRANSFORM_F); 
//	Data_write();
//	Data_read();
//	MCU_CSlow();                                                                // CS low begins SPI transaction
	
	while (1)
	{
	//	Ft_Main__Update();
	//	 APP_SliderandButton();
//		osDelay(1000);
//			cmdOffset = EVE_WaitCmdFifoEmpty();   
//		EVE_AddrForWr(RAM_CMD + cmdOffset);                                         // Send address to which first value will be written

//		EVE_Write32(CMD_DLSTART);
//		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);

//		EVE_Write32(CLEAR_COLOR_RGB(22, 22, 22));                                        // Set the default clear color to black
//		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);

//		EVE_Write32(CLEAR(1,1,1));                                                  // Clear the screen Attributes color, stencil and tag buffers
//		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);
//			EVE_Write32 (CMD_LOGO);                                                     // command text 0xFFFFFF0C
////	EVE_Write16 (400);                                                          // x
////	EVE_Write16 (240);                                                          // y
////	EVE_Write16 (0);                                                           // font
////	EVE_Write16 (0);                                                            // options
//		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);  
//		EVE_Write32(END());
//		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);
//		EVE_Write32(DISPLAY());
//		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);
//		EVE_Write32(CMD_SWAP);
//		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);
//		MCU_CShigh();                                                           // Chip Select high concludes burst
//		EVE_MemWrite32(REG_CMD_WRITE, (cmdOffset));          

//cmd_spinner(80, 60, 0, 0);
	/*	cmdOffset = EVE_WaitCmdFifoEmpty();                                         // Wait for command FIFO to be empty and record current position in FIFO

		MCU_CSlow();                                                                // CS low begins SPI transaction
		EVE_AddrForWr(RAM_CMD + cmdOffset);                                         // Send address to which first value will be written

		EVE_Write32(CMD_DLSTART);
		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);

		EVE_Write32(CLEAR_COLOR_RGB(0,0,0));                                        // Set the default clear color to black
		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);

		EVE_Write32(CLEAR(1,1,1));                                                  // Clear the screen Attributes color, stencil and tag buffers
		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);
		EVE_Write32(COLOR_RGB(255, 0, 0));
		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);

		EVE_Write32(  POINT_SIZE(ch * 16));
		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);
		EVE_Write32(BEGIN(FTPOINTS));
		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);
		EVE_Write32( VERTEX2F(400 * 16, 240 * 16));
		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);
		EVE_Write32(END());
		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);
		EVE_Write32(DISPLAY());
		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);
		EVE_Write32(CMD_SWAP);
		cmdOffset = EVE_IncCMDOffset(cmdOffset, 4);
		MCU_CShigh();                                                           // Chip Select high concludes burst
		EVE_MemWrite32(REG_CMD_WRITE, (cmdOffset));                             // Update the ring buffer pointer                                                           // Co-processor will now execute all of the above commands and create a display list
		cmdOffset = EVE_WaitCmdFifoEmpty();
		osDelay(100);
		ch--;
		if (ch<1)
			ch=480;*/
	}


}








