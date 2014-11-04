#include"Task_GUI.h"
// #include"GUIDEMO.h"
//#include<songti16.c>
//#include<SongTi24.c>
//#include<songti48.c>
//#include<zhandian16.c>
#include"LCD_interface.h"
#include"Bsp_Touch_SPI.h"
#include"GUI_DraweSing.h"
#include "MainTaskGUI.h"
#include"time.h"
#include"stdio.h"
#include"stdlib.h"
void AppTaskGUI(void *p_arg)
{
//	uint8_t i;
	GUI_COLOR Colorsback;
	OS_ERR      err;
  OSTimeGet(&err);	
	(void) p_arg;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);   // 开启CRC 功能
	
	Lcd_Init();   // LCD 初始化 
	
  Touch_Init();  // 显示屏初始化 
	
 	
  WM_SetCreateFlags(WM_CF_MEMDEV); // 开启 窗口 内存允许
  GUI_Init();	    // ＧＵＩ开始 
	GUI_Clear();    // 清屏 
	// FistPageDrawLine();
	// CPU_SR_ALLOC();
	// CPU_CRITICAL_ENTER(); // 禁止中断
	backWIn_init();  //调用显示屏显示界面
  Draw_init();
// 	GUI_CURSOR_Show();    //显示指针 
   pageChangFlag=0;
	 while(1)
	 {
		 if(pageChangFlag)
		 {
			 
			 GUI_SelectLayer(1);
			 GUI_TOUCH_SetLayer(1);	
			 Colorsback=GUI_GetBkColor();
		   GUI_SetBkColor(GUI_DARKBLUE);
		   GUI_SetFont(GUI_FONT_8X16);	
			 GUI_DispStringAt("Station : ",10,10);				 
       GUI_DispDec(pageChangFlag,1);	
			 GUI_GotoXY(98,39);
			 GUI_DispFloat(getInformation[pageChangFlag-1].K_tmp,4);
			 GUI_GotoXY(98,58);
			 GUI_DispFloat(getInformation[pageChangFlag-1].K_hemo,4);
			 GUI_GotoXY(336,39);
			 GUI_DispFloat(getInformation[pageChangFlag-1].T_tmp,4);
			 GUI_GotoXY(336,58);
			 GUI_DispFloat(getInformation[pageChangFlag-1].T_hemp,4);
		   GUI_SetBkColor(Colorsback);
			 DrawingNewAnew(pageChangFlag);
	     COMAND=0x04;    // 显示页面 
	     DATA=1;	
			 GUI_Delay(100);
		 }else 
		 {
			 GUI_SelectLayer(0);
			 GUI_TOUCH_SetLayer(0);		
	     COMAND=0x04;    // 显示页面 
	     DATA=0;				 
			 showShuJu();
		 }
		 GUI_Delay(300);
	 }
}
void AppTaskGUIDrawing(void *p_arg)
{
	p_arg=p_arg;
	while(1)
	{
		
	}
	 
}
void AppTaskGUIRefresh(void *p_arg)
{
  (void)p_arg;
	while(1)
	{
		  // GUI_Exec();             //    GUI 切换
		  GUI_TOUCH_Exec();	     //    触摸屏切换
		  BSP_OS_TimeDly(15);
	}
}
