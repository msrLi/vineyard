
#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"

#include "WM.h"
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "PROGBAR.h"
#include "SCROLLBAR.h"
#include "LISTVIEW.h"
#include "MULTIPAGE.h"



/*********************************************************************
*
*       static data
*
**********************************************************************
*/

#define GUI_ID_BUTTON10   GUI_ID_USER+1
#define GUI_ID_BUTTON11   GUI_ID_USER+2
#define GUI_ID_BUTTON13   GUI_ID_USER+4
#define GUI_ID_BUTTON12   GUI_ID_USER+3
#define GUI_ID_BUTTON14   GUI_ID_USER+5
#define GUI_ID_BUTTON15   GUI_ID_USER+6

/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreateSelect[] = {
	{ WINDOW_CreateIndirect,    "Dialog 3",              0,                   10,   0, 370, 180, FRAMEWIN_CF_MOVEABLE },
	{ CHECKBOX_CreateIndirect,  "Sine",              GUI_ID_CHECK0,           23, 15, 59, 20, 0,0},
    { CHECKBOX_CreateIndirect,  "Triangular",        GUI_ID_CHECK2,           23, 73, 107,20, 0,0},
    { CHECKBOX_CreateIndirect,  "Square ",           GUI_ID_CHECK1,           23, 44, 83, 20, 0,0},
    { CHECKBOX_CreateIndirect,  "DC",                GUI_ID_CHECK3,           23, 102,43, 20, 0,0},
    { CHECKBOX_CreateIndirect,  "Niose",             GUI_ID_CHECK4,           23, 131,67, 20, 0,0}
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialogSelect(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialogSelect(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //GUI_ID_CHECK0
    //
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECK0),"Sine");
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECK0),&GUI_Font16B_1);
    //
    //GUI_ID_CHECK2
    //
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECK2),"Triangular");
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECK2),&GUI_Font16B_1);
    //
    //GUI_ID_CHECK1
    //
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECK1),"Square");
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECK1),&GUI_Font16B_1);
    //
    //GUI_ID_CHECK3
    //
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECK3),"DC");
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECK3),&GUI_Font16B_1);
    //
    //GUI_ID_CHECK4
    //
    CHECKBOX_SetText(WM_GetDialogItem(hWin,GUI_ID_CHECK4),"Niose");
    CHECKBOX_SetFont(WM_GetDialogItem(hWin,GUI_ID_CHECK4),&GUI_Font16B_1);

}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbDialogSelect(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialogSelect(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialogSelect(pMsg);
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (Id) 
            {
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;

            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}
/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreateSquare[] = {
	{ WINDOW_CreateIndirect,    "Dialog 3",              0,                   10,   0, 370, 180, FRAMEWIN_CF_MOVEABLE },
	{ TEXT_CreateIndirect,      "DutyCycle",         GUI_ID_TEXT0,            151,2,  80, 16, 0,0},
    { TEXT_CreateIndirect,      "Frequency",         GUI_ID_TEXT1,            151,46, 80, 16, 0,0},
    { TEXT_CreateIndirect,      "Amplitude",         GUI_ID_TEXT2,            151,100,80, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT2,            208,21, 93, 22, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT3,            208,65, 93, 22, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT4,            208,127,93, 22, 0,0},
    { SLIDER_CreateIndirect,     NULL,               GUI_ID_SLIDER1,          66, 22, 118,21, 0,0},
    { SLIDER_CreateIndirect,     NULL,               GUI_ID_SLIDER2,          66, 65, 118,21, 0,0},
    { SLIDER_CreateIndirect,     NULL,               GUI_ID_SLIDER3,          66, 128,118,21, 0,0},
    { TEXT_CreateIndirect,      "V",                 GUI_ID_TEXT5,            307,130,16, 16, 0,0},
    { TEXT_CreateIndirect,      "Hz",                GUI_ID_TEXT4,            307,72, 24, 16, 0,0},
    { TEXT_CreateIndirect,      "%",                 GUI_ID_TEXT3,            307,24, 16, 16, 0,0},
//    { BUTTON_CreateIndirect,    "OK",                GUI_ID_BUTTON14,         36, 157,88, 25, 0,0},
//    { BUTTON_CreateIndirect,    "CANCEL",            GUI_ID_BUTTON15,         268,157,88, 25, 0,0}
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialogSquare(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialogSquare(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //GUI_ID_TEXT0
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT0),&GUI_Font16B_1);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT1),&GUI_Font16B_1);
    //
    //GUI_ID_TEXT2
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT2),&GUI_Font16B_1);
    //
    //GUI_ID_EDIT2
    //
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT2),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_EDIT3
    //
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT3),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_EDIT4
    //
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT4),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT5
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT5),&GUI_Font16B_1);
    //
    //GUI_ID_TEXT4
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT4),&GUI_Font16B_1);
    //
    //GUI_ID_TEXT3
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT3),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON14
    //
  //  BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON14),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON15
    //
  //  BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON15),&GUI_Font16B_1);

}




/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbDialogSquare(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialogSquare(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialogSquare(pMsg);
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (Id) 
            {
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;

            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}
/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreateSine[] = {
	{ WINDOW_CreateIndirect,    "Dialog 1",              0,                   10,   0, 370, 180, FRAMEWIN_CF_MOVEABLE },
//	{ BUTTON_CreateIndirect,    "OK",                GUI_ID_BUTTON0,          33, 163,92, 22, 0,0},
//  { BUTTON_CreateIndirect,    "CANCEL",            GUI_ID_BUTTON1,          276,163,92, 22, 0,0},
    { TEXT_CreateIndirect,      "Amplitude ",        GUI_ID_TEXT0,            44, 5,  88, 16, 0,0},
    { BUTTON_CreateIndirect,    "1",                 GUI_ID_BUTTON2,          236,30, 30, 30, 0,0},
    { BUTTON_CreateIndirect,    "8",                 GUI_ID_BUTTON9,          335,65, 30, 30, 0,0},
    { BUTTON_CreateIndirect,    "9",                 GUI_ID_BUTTON10,         236,99, 30, 30, 0,0},
    { BUTTON_CreateIndirect,    "5",                 GUI_ID_BUTTON6,          236,65, 30, 30, 0,0},
    { BUTTON_CreateIndirect,    "6",                 GUI_ID_BUTTON7,          269,65, 30, 30, 0,0},
    { BUTTON_CreateIndirect,    "7",                 GUI_ID_BUTTON8,          302,65, 30, 30, 0,0},
    { BUTTON_CreateIndirect,    "4",                 GUI_ID_BUTTON5,          335,30, 30, 30, 0,0},
    { BUTTON_CreateIndirect,    "0",                 GUI_ID_BUTTON11,         268,99, 30, 30, 0,0},
    { BUTTON_CreateIndirect,    "3",                 GUI_ID_BUTTON4,          302,30, 30, 30, 0,0},
    { BUTTON_CreateIndirect,    "2",                 GUI_ID_BUTTON3,          269,30, 30, 30, 0,0},
    { SLIDER_CreateIndirect,     NULL,               GUI_ID_SLIDER0,          14, 65, 139,24, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT0,            14, 132,118,22, 0,0},
    { TEXT_CreateIndirect,      "V",                 GUI_ID_TEXT1,            138,135,16, 16, 0,0},
    { EDIT_CreateIndirect,       NULL,               GUI_ID_EDIT1,            235,132,92, 22, 0,0},
    { TEXT_CreateIndirect,      "Hz",                GUI_ID_TEXT2,            336,135,24, 16, 0,0},
    { TEXT_CreateIndirect,      "Frequency",         GUI_ID_TEXT3,            259,5,  80, 16, 0,0},
    { BUTTON_CreateIndirect,    ".",                 GUI_ID_BUTTON13,         335,99, 30, 30, 0,0},
    { BUTTON_CreateIndirect,    "C",                 GUI_ID_BUTTON12,         302,99, 30, 30, 0,0}
};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialogSine(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialogSine(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //GUI_ID_BUTTON0
    //
 //   BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON1
    //
 //   BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),&GUI_Font16B_1);
    //
    //GUI_ID_TEXT0
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT0),&GUI_Font16B_1);
    TEXT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_TEXT0),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_BUTTON2
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON2),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON9
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON9),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON10
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON10),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON6
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON6),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON7
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON7),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON8
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON8),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON5
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON5),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON11
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON11),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON4
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON4),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON3
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON3),&GUI_Font16B_1);
    //
    //GUI_ID_EDIT0
    //
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT0),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT1
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT1),&GUI_Font16B_1);
    //
    //GUI_ID_EDIT1
    //
    EDIT_SetTextAlign(WM_GetDialogItem(hWin,GUI_ID_EDIT1),GUI_TA_VCENTER|GUI_TA_CENTER);
    //
    //GUI_ID_TEXT2
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT2),&GUI_Font16B_1);
    //
    //GUI_ID_TEXT3
    //
    TEXT_SetFont(WM_GetDialogItem(hWin,GUI_ID_TEXT3),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON13
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON13),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON12
    //
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON12),&GUI_Font16B_1);

}
/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbDialogSine(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
	case WM_PAINT:
		PaintDialogSine(pMsg);
		break;
	case WM_INIT_DIALOG:
		InitDialogSine(pMsg);
		break;
	case WM_KEY:
		switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
		{
		case GUI_KEY_ESCAPE:
			GUI_EndDialog(hWin, 1);
			break;
		case GUI_KEY_ENTER:
			GUI_EndDialog(hWin, 0);
			break;
		}
		break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (Id) 
            {
			case GUI_ID_OK:
				if(NCode==WM_NOTIFICATION_RELEASED)
					GUI_EndDialog(hWin, 0);
				break;
			case GUI_ID_CANCEL:
				if(NCode==WM_NOTIFICATION_RELEASED)
					GUI_EndDialog(hWin, 0);
				break;		
            }
            break;
			default:
				WM_DefaultProc(pMsg);
    }
}
/*********************************************************************
*
*       Dialog resource
*
* This table conatins the info required to create the dialog.
* It has been created by ucGUIbuilder.
*/

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect,  "DAC Configuration", 0,                       0,  0,  400,240,FRAMEWIN_CF_MOVEABLE,0},
	{ BUTTON_CreateIndirect,    "OK",                GUI_ID_BUTTON0,          31, 184,99, 27, 0,0},
    { BUTTON_CreateIndirect,    "CANCEL",            GUI_ID_BUTTON1,          264,184,99, 27, 0,0}

};



/*****************************************************************
**      FunctionName:void PaintDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_PAINT
*****************************************************************/

void PaintDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

}



/*****************************************************************
**      FunctionName:void InitDialog(WM_MESSAGE * pMsg)
**      Function: to initialize the Dialog items
**                                                      
**      call this function in _cbCallback --> WM_INIT_DIALOG
*****************************************************************/

void InitDialog(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    //
    //FRAMEWIN
    //
    FRAMEWIN_SetBarColor(hWin,1,0x00fc7c);
    FRAMEWIN_SetTextColor(hWin,0x0000ff);
    FRAMEWIN_SetFont(hWin,&GUI_Font16B_ASCII);
    FRAMEWIN_SetTextAlign(hWin,GUI_TA_VCENTER|GUI_TA_CENTER);
    FRAMEWIN_SetTitleHeight(hWin,18);
	FRAMEWIN_SetMoveable(hWin,0);

	//
    //GUI_ID_BUTTON0
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),BUTTON_CI_UNPRESSED,0x00d7ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON0),&GUI_Font16B_1);
    //
    //GUI_ID_BUTTON1
    //
    BUTTON_SetBkColor(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),BUTTON_CI_UNPRESSED,0x00d7ff);
    BUTTON_SetFont(WM_GetDialogItem(hWin,GUI_ID_BUTTON1),&GUI_Font16B_1);

}
/*********************************************************************
*
*       Dialog callback routine
*/
static void _cbCallback(WM_MESSAGE * pMsg) 
{
    int NCode, Id;
    WM_HWIN hWin = pMsg->hWin;
    switch (pMsg->MsgId) 
    {
        case WM_PAINT:
            PaintDialog(pMsg);
            break;
        case WM_INIT_DIALOG:
            InitDialog(pMsg);
            break;
        case WM_KEY:
            switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key) 
            {
                case GUI_KEY_ESCAPE:
                    GUI_EndDialog(hWin, 1);
                    break;
                case GUI_KEY_ENTER:
                    GUI_EndDialog(hWin, 0);
                    break;
            }
            break;
        case WM_NOTIFY_PARENT:
            Id = WM_GetId(pMsg->hWinSrc); 
            NCode = pMsg->Data.v;        
            switch (Id) 
            {
                case GUI_ID_OK:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;
                case GUI_ID_CANCEL:
                    if(NCode==WM_NOTIFICATION_RELEASED)
                        GUI_EndDialog(hWin, 0);
                    break;

            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}
/*********************************************************************
*
*       MainTask
*
**********************************************************************
*/
void MainTask(void) 
{ 
	WM_HWIN hMultiPage, hDialog,hDialogTemp;
    GUI_Init();
	GUI_CURSOR_Show();		 
    WM_SetDesktopColor(GUI_WHITE);    /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
	WM_EnableMemdev(WM_HBKWIN);

    hDialog=GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbCallback, 0, 0, 0);
	hMultiPage = MULTIPAGE_CreateEx(0, 0, 393, 180, WM_GetClientWindow(hDialog), WM_CF_SHOW, 0, 0);

	hDialogTemp = GUI_CreateDialogBox(_aDialogCreateSelect,   //信号源选择
		GUI_COUNTOF(_aDialogCreateSelect), 
		&_cbDialogSelect, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(hMultiPage, hDialogTemp, "Select");

	hDialogTemp = GUI_CreateDialogBox(_aDialogCreateSine,     //正弦波
		GUI_COUNTOF(_aDialogCreateSine), 
		&_cbDialogSine, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(hMultiPage, hDialogTemp, "Sine");

	hDialogTemp = GUI_CreateDialogBox(_aDialogCreateSquare,   //方波
		GUI_COUNTOF(_aDialogCreateSquare), 
		&_cbDialogSquare, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(hMultiPage, hDialogTemp, "Square");



// 	hDialogTemp = GUI_CreateDialogBox(_aDialogCreate4, 
// 		GUI_COUNTOF(_aDialogCreate4), 
// 		&_cbDialog4, WM_UNATTACHED, 0, 0);
// 	MULTIPAGE_AddPage(hMultiPage, hDialogTemp, "Page 4");
// 	hDialogTemp = GUI_CreateDialogBox(_aDialogCreate5, 
// 		GUI_COUNTOF(_aDialogCreate5), 
// 		&_cbDialog5, WM_UNATTACHED, 0, 0);
//   MULTIPAGE_AddPage(hMultiPage, hDialogTemp, "Page 5");
	while(1)
	{						 
		GUI_Delay(50);
		
	}
	
}