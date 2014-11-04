/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2013  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.22 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  ARM LIMITED whose registered office
is situated at  110 Fulbourn Road,  Cambridge CB1 9NJ,  England solely
for  the  purposes  of  creating  libraries  for  ARM7, ARM9, Cortex-M
series,  and   Cortex-R4   processor-based  devices,  sublicensed  and
distributed as part of the  MDK-ARM  Professional  under the terms and
conditions  of  the   End  User  License  supplied  with  the  MDK-ARM
Professional. 
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUIDRV_Lin.h"

/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/
//
// Physical display size
//
#define XSIZE_PHYS 480
#define YSIZE_PHYS 272
//#define VXSIZE_PHYS 400
//#define VYSIZE_PHYS 280
#define LCD_BITSPERPIXEL       16
#define LCD_USE_PARALLEL_16     0
//
// Color conversion
//
#define COLOR_CONVERSION GUICC_M565    // ÑÕÉ«565 
//
// Display driver
//
#define DISPLAY_DRIVER &GUIDRV_Template_API
//
// Orientation
//
#define DISPLAY_ORIENTATION  GUI_SWAP_XY | GUI_MIRROR_X | GUI_MIRROR_Y
//
// Configures touch screen module
//
#define GUI_TOUCH_AD_LEFT 	 1965
#define GUI_TOUCH_AD_RIGHT 	 80
#define GUI_TOUCH_AD_TOP 	 1928
#define GUI_TOUCH_AD_BOTTOM  201


/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/

#ifndef   VRAM_ADDR
  #define VRAM_ADDR 0 // TBD by customer: This has to be the frame buffer start address
#endif

#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
	
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
	
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
	
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif
	
#ifndef   NUM_VSCREENS
  #define NUM_VSCREENS 1
#else
	 
#if (NUM_VSCREENS <= 0)
  #error At least one screeen needs to be defined!
  #endif
#endif
#if (NUM_VSCREENS > 1) && (NUM_BUFFERS > 1)
  #error Virtual screens and multiple buffers are not allowed!
#endif

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*   
*/
void LCD_X_Config(void) {
  //
  // At first initialize use of multiple buffers on demand
  //
  #if (NUM_BUFFERS > 1)
  int i;

  for (i = 0; i < GUI_NUM_LAYERS; i++) {
    GUI_MULTIBUF_ConfigEx(i, NUM_BUFFERS);
  }
  #endif
  //
  // Set display driver and color conversion for 1st layer
  //
  GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
	GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 1);
	GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 2);
	GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 3);
	GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 4);
	GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 5);
  //
  // Display driver configuration, required for Lin-driver
  //
  if (LCD_GetSwapXY()) {
    LCD_SetSizeEx (0, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(0, YSIZE_PHYS * NUM_VSCREENS, XSIZE_PHYS);
    LCD_SetSizeEx (1, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(1, YSIZE_PHYS * NUM_VSCREENS, XSIZE_PHYS);
    LCD_SetSizeEx (2, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(2, YSIZE_PHYS * NUM_VSCREENS, XSIZE_PHYS);
    LCD_SetSizeEx (3, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(3, YSIZE_PHYS * NUM_VSCREENS, XSIZE_PHYS);
  } else {
    LCD_SetSizeEx (0, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS * NUM_VSCREENS);
    LCD_SetSizeEx (1, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(1, XSIZE_PHYS, YSIZE_PHYS * NUM_VSCREENS);
    LCD_SetSizeEx (2, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(2, XSIZE_PHYS, YSIZE_PHYS * NUM_VSCREENS);
    LCD_SetSizeEx (3, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(3, XSIZE_PHYS, YSIZE_PHYS * NUM_VSCREENS);
  }
  // LCD_SetVRAMAddrEx(0, (void *)VRAM_ADDR);
  //
  // Set user palette data (only required if no fixed palette is used)
  //
  #if defined(PALETTE)
    LCD_SetLUTEx(0, PALETTE);
		LCD_SetLUTEx(1, PALETTE);
		LCD_SetLUTEx(2, PALETTE);
		LCD_SetLUTEx(3, PALETTE);
		LCD_SetLUTEx(4, PALETTE);
		LCD_SetLUTEx(5, PALETTE);
  #endif
 			/* Touch calibration */
 		  //	GUI_TOUCH_SetOrientation(0);     // ÉèÖÃ ´¥ÃþÆÁ Î»ÖÃ×ø±ê
//	GUI_TOUCH_SetOrientation(0);
	GUI_TOUCH_Calibrate(GUI_COORD_X, 0, XSIZE_PHYS - 1, GUI_TOUCH_AD_LEFT,  GUI_TOUCH_AD_RIGHT);
	GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, YSIZE_PHYS - 1, GUI_TOUCH_AD_TOP,  GUI_TOUCH_AD_BOTTOM);	
//	GUI_TOUCH_SetOrientation(1);
	
//	GUI_TOUCH_Calibrate(GUI_COORD_X, 1, XSIZE_PHYS - 1, GUI_TOUCH_AD_LEFT,  GUI_TOUCH_AD_RIGHT);
//	GUI_TOUCH_Calibrate(GUI_COORD_Y, 1, YSIZE_PHYS - 1, GUI_TOUCH_AD_TOP,  GUI_TOUCH_AD_BOTTOM);	
////	GUI_TOUCH_SetOrientation(2);
//	GUI_TOUCH_Calibrate(GUI_COORD_X, 2, XSIZE_PHYS - 1, GUI_TOUCH_AD_LEFT,  GUI_TOUCH_AD_RIGHT);
//	GUI_TOUCH_Calibrate(GUI_COORD_Y, 2, YSIZE_PHYS - 1, GUI_TOUCH_AD_TOP,  GUI_TOUCH_AD_BOTTOM);	
////	GUI_TOUCH_SetOrientation(3);
//	GUI_TOUCH_Calibrate(GUI_COORD_X, 3, XSIZE_PHYS - 1, GUI_TOUCH_AD_LEFT,  GUI_TOUCH_AD_RIGHT);
//	GUI_TOUCH_Calibrate(GUI_COORD_Y, 3, YSIZE_PHYS - 1, GUI_TOUCH_AD_TOP,  GUI_TOUCH_AD_BOTTOM);	
   LCD_SetVisEx(0, 1);
	 LCD_SetVisEx(1, 1);
	 LCD_SetVisEx(2, 1);
	 LCD_SetVisEx(3, 1);
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if 
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
	
  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    // ...
    return 0;
  }
  case LCD_X_SETVRAMADDR: {
    //
    // Required for setting the address of the video RAM for drivers
    // with memory mapped video RAM which is passed in the 'pVRAM' element of p
    //
    LCD_X_SETVRAMADDR_INFO * p;
		(void) p;
    p = (LCD_X_SETVRAMADDR_INFO *)pData;
    //...
    return 0;
  }
  case LCD_X_SETORG: {
    //
    // Required for setting the display origin which is passed in the 'xPos' and 'yPos' element of p
    //
    LCD_X_SETORG_INFO * p;
		(void) p;
    p = (LCD_X_SETORG_INFO *)pData;
    //...
    return 0;
  }
  case LCD_X_SHOWBUFFER: {
    //
    // Required if multiple buffers are used. The 'Index' element of p contains the buffer index.
    //
    LCD_X_SHOWBUFFER_INFO * p;
		(void) p;
    p = (LCD_X_SHOWBUFFER_INFO *)pData;
    //...
    return 0;
  }
  case LCD_X_SETLUTENTRY: {
    //
    // Required for setting a lookup table entry which is passed in the 'Pos' and 'Color' element of p
    //
    LCD_X_SETLUTENTRY_INFO * p;
		(void) p;
    p = (LCD_X_SETLUTENTRY_INFO *)pData;
    //...
    return 0;
  }
  case LCD_X_ON: {
    //
    // Required if the display controller should support switching on and off
    //
    return 0;
  }
  case LCD_X_OFF: {
    //
    // Required if the display controller should support switching on and off
    //
    // ...
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/
