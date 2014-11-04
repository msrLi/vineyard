/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2012  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.16 - Graphical user interface for embedded applications **
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
File        : GUIDEMO_Start.c
Purpose     : GUIDEMO initialization
----------------------------------------------------------------------
*/

#include "GUIDEMO.h"

/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
  WM_SetCreateFlags(WM_CF_MEMDEV);
  GUI_Init();
  GUIDEMO_Main();
}


///*************************** End of file ****************************/
//
//
//
//#include <stddef.h>
//#include "GUI.h"
//#include "DIALOG.h"
//
//#include "WM.h"
//#include "BUTTON.h"
//#include "CHECKBOX.h"
//#include "DROPDOWN.h"
//#include "EDIT.h"
//#include "FRAMEWIN.h"
//#include "LISTBOX.h"
//#include "MULTIEDIT.h"
//#include "RADIO.h"
//#include "SLIDER.h"
//#include "TEXT.h"
//#include "PROGBAR.h"
//#include "SCROLLBAR.h"
//#include "LISTVIEW.h"
//
//
//
//
//
////EventsFunctionList
////EndofEventsFunctionList
//
//
///*********************************************************************
//*
//*       static data
//*
//**********************************************************************
//*/
//
//
//
///*********************************************************************
//*
//*       Dialog resource
//*
//* This table conatins the info required to create the dialog.
//* It has been created by ucGUIbuilder.
//*/
//
//static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
//    { FRAMEWIN_CreateIndirect,  "emWin",             0,                       0,  0,  480,272,0,0},
//    { MULTIEDIT_CreateIndirect, "MULTIEDIT",         GUI_ID_MULTIEDIT0,       35, 46, 100,96, 0,0},
//    { SCROLLBAR_CreateIndirect,  NULL,               GUI_ID_SCROLLBAR0,       174,46, 172,15, 0,0},
//    { PROGBAR_CreateIndirect,    NULL,               GUI_ID_PROGBAR0,         35, 173,184,30, 0,0},
//    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT0,            45, 278,100,21, 0,0},
//    { DROPDOWN_CreateIndirect,   NULL,               GUI_ID_DROPDOWN0,        186,91, 146,80, 0,0},
//    { BUTTON_CreateIndirect,    "BUTTON0",           GUI_ID_BUTTON0,          236,169,132,38, 0,0}
//};
//
//
//
///*****************************************************************
//**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
//**      Function: to initialize the Dialog items
//**                                                      
//**      call this function in _cbCallback --> WM_PAINT
//*****************************************************************/
//
//void PaintDialog(WM_MESSAGE * pMsg)
//{
//    WM_HWIN hWin = pMsg->hWin;
//
//}
//
//
//
///*****************************************************************
//**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
//**      Function: to initialize the Dialog items
//**                                                      
//**      call this function in _cbCallback --> WM_INIT_DIALOG
//*****************************************************************/
//
//void InitDialog(WM_MESSAGE * pMsg)
//{
//    WM_HWIN hWin = pMsg->hWin;
//    //
//    //FRAMEWIN
//    //
//	FRAMEWIN_SetClientColor(hWin,0x0000ff);
//    FRAMEWIN_SetTextColor(hWin,0x0000ff);
//    FRAMEWIN_SetFont(hWin,&GUI_Font24B_ASCII);
//    FRAMEWIN_SetTextAlign(hWin,GUI_TA_VCENTER|GUI_TA_CENTER);
//    FRAMEWIN_AddCloseButton(hWin, FRAMEWIN_BUTTON_RIGHT, 0);
//    FRAMEWIN_AddMaxButton(hWin, FRAMEWIN_BUTTON_RIGHT, 1);
//    FRAMEWIN_AddMinButton(hWin, FRAMEWIN_BUTTON_RIGHT, 2);
//    FRAMEWIN_SetTitleHeight(hWin,20);
//    //
//    //GUI_ID_PROGBAR0
//    //
//    PROGBAR_SetText(WM_GetDialogItem(hWin,GUI_ID_PROGBAR0),"PROGBAR0");
//    PROGBAR_SetValue(WM_GetDialogItem(hWin,GUI_ID_PROGBAR0),50);
//    //
//    //GUI_ID_DROPDOWN0
//    //
//    DROPDOWN_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_DROPDOWN0),0,0xffffff);
//
//}
//
///*********************************************************************
//*
//*       Dialog callback routine
//*/
//static void _cbCallback(WM_MESSAGE * pMsg) 
//{
//    int NCode, Id;
//    WM_HWIN hWin = pMsg->hWin;
//    switch (pMsg->MsgId) 
//    {
//        case WM_PAINT:
//            PaintDialog(pMsg);
//            break;
//        case WM_INIT_DIALOG:
//            InitDialog(pMsg);
//            break;
//        case WM_KEY:
//            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
//            {
//                case GUI_KEY_ESCAPE:
//                    GUI_EndDialog(hWin, 1);
//                    break;
//                case GUI_KEY_ENTER:
//                    GUI_EndDialog(hWin, 0);
//                    break;
//            }
//            break;
//        case WM_NOTIFY_PARENT:
//            Id = WM_GetId(pMsg->hWinSrc); 
//            NCode = pMsg->Data.v;        
//            switch (Id) 
//            {
//                case GUI_ID_OK:
//                    if(NCode==WM_NOTIFICATION_RELEASED)
//                        GUI_EndDialog(hWin, 0);
//                    break;
//                case GUI_ID_CANCEL:
//                    if(NCode==WM_NOTIFICATION_RELEASED)
//                        GUI_EndDialog(hWin, 0);
//                    break;
//
//            }
//            break;
//        default:
//            WM_DefaultProc(pMsg);
//    }
//}
//
//
///*********************************************************************
//*
//*       MainTask
//*
//**********************************************************************
//*/
//void MainTask(void) 
//{ 
//    GUI_Init();
//	GUI_CURSOR_Show();
//    WM_SetDesktopColor(GUI_WHITE);    /* Automacally update desktop window */
//    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
//	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
//	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
//	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
//	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
//	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
//	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
//	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
//	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
//	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
//	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
//    GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
//	while(1)
//	{
//		GUI_Delay(10);
//		GUI_TOUCH_Exec();	
//	}
//}
