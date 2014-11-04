#include"LCD_interface.h"
#include<wenshiduSongTi16.c>
#include<nongyeyun48.c>
#define DrawLine_H01  72   //中间第一条水平线 
#define DrawLine_H02  172   //中间第二条水平线 
#define H03_Line_Far  100    // 线间距
float ST_Temp[8]={20};
float SK_Temp[8]={15};
float ST_Hemp[8]={10};
float SK_Hemp[8]={35};
void FistPageDrawLine(void)
{
//	GUI_RECT  pRect;
	int xSize, ySize;
	uint32_t i,j,k;
	uint32_t V01_Size;  // 竖向平均像素点 
	uint32_t OrginX,OrginY;
	GUI_SetColor(GUI_DARKGRAY);
	xSize=LCD_GetXSize();
	ySize=LCD_GetYSize();
	ySize=ySize;
	/* 画外围框  */
////	GUI_DrawLine(0,0,xSize-1,0);
////	GUI_DrawLine(0,0,0,ySize-1);	
////	GUI_DrawLine(0,ySize-1,xSize-1,ySize-1);
////	GUI_DrawLine(xSize-1,0,xSize-1,ySize-1);
////	GUI_DrawLine(0,DrawLine_H01-1,xSize-1,DrawLine_H01-1);
////	GUI_DrawLine(0,DrawLine_H02-1,xSize-1,DrawLine_H02-1);
	V01_Size=xSize/4;
	i=V01_Size;
	for(j=0;j<4;j++)
	{
//		GUI_DrawVLine(i,DrawLine_H01-1,ySize-1);
		i+=V01_Size;
	}
	
	for(i=0;i<5;i++)
	{
		/* 画 水平线 */ 
		GUI_SetColor(GUI_GRAY);
		OrginX=1+V01_Size*i;
		OrginY=DrawLine_H01+2;
		k=OrginY;
	  //GUI_DrawLine(OrginX,OrginY+24,OrginX+40,OrginY+48);
		   
		for(j=0;j<4;j++)
		{
			GUI_DrawHLine(k,OrginX,V01_Size*(i+1)-3);
			k+=24;
		}
		GUI_DrawHLine(k-1,OrginX,V01_Size*(i+1)-3);
		/* 画 竖直 线 */
		GUI_DrawVLine(OrginX,OrginY,DrawLine_H02-3);
		GUI_DrawVLine(OrginX+116,OrginY,DrawLine_H02-3);
		
		GUI_DrawVLine(OrginX+42,OrginY+24,DrawLine_H02-3);
		GUI_DrawVLine(OrginX+80,OrginY+24,DrawLine_H02-3);
	}
	/* 下四个 */
	for(i=0;i<5;i++)
	{
		/* 画 水平线 */ 
		GUI_SetColor(GUI_GRAY);
		OrginX=1+V01_Size*i;
		OrginY=DrawLine_H02+2;
		k=OrginY;
		//GUI_DrawLine(OrginX,OrginY+24,OrginX+40,OrginY+48);
		for(j=0;j<4;j++)
		{
			GUI_DrawHLine(k,OrginX,V01_Size*(i+1)-3);
			k+=24;
		}
		GUI_DrawHLine(k-1,OrginX,V01_Size*(i+1)-3);
		/* 画 竖直 线 */
		GUI_DrawVLine(OrginX,OrginY,OrginY+H03_Line_Far-5);
		GUI_DrawVLine(OrginX+116,OrginY,OrginY+H03_Line_Far-5);
		
		GUI_DrawVLine(OrginX+42,OrginY+24,OrginY+H03_Line_Far-5);
		GUI_DrawVLine(OrginX+80,OrginY+24,OrginY+H03_Line_Far-5);
	}
   show_temp();
}
void showShuJu(void)
{
	uint32_t OrigX,OrigY;
   float fdsa=0;
	uint8_t i,j;
	GUI_SetColor(GUI_DARKGRAY);
	OrigX=LCD_GetXSize();
	OrigX=OrigX/2;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
		
			OrigX=(i==0)?	46+120*i:47+120*i;
			OrigY=127+100*j;
			GUI_SetFont(GUI_FONT_8X16);
			GUI_SetColor(GUI_YELLOW);
			GUI_GotoXY(OrigX,OrigY);
			fdsa=getInformation[i+j*4].K_tmp;
			GUI_DispFloat(fdsa,4);
		
			GUI_GotoXY(OrigX+36,OrigY);
			fdsa=getInformation[i+j*4].K_hemo;
			GUI_DispFloat(fdsa,4);	

			GUI_GotoXY(OrigX,OrigY+24);
			fdsa=getInformation[i+j*4].T_tmp;
			GUI_DispFloat(fdsa,4);

			GUI_GotoXY(OrigX+36,OrigY+24);
			fdsa=getInformation[i+j*4].T_hemp;
			GUI_DispFloat(fdsa,4);
		}			
	}	
}
void show_temp(void)
{
	
	uint32_t OrigX,OrigY;
	float fdsa=0;
	uint8_t i,j,t;
	static const char *_S_tile[]={
  "\xe5\x86\x9c\xe4\xb8\x9a\xe7\x89\xa9\xe8\x81\x94\xe7\xbd\x91\xe4\xba\x91\xe7\x9b\x91\xe6\xb5\x8b\xe7\xb3\xbb\xe7\xbb\x9f"
	};
	static const char * _apStringWWW[]={
	"http://www.macrobot.cn/"
	};
	static const char * _S_note[]={   // 节电 
		"\xe8\x8a\x82\xe7\x82\xb9"
	};
	static const char *_S_number[]={  // 数字 
		"1","2","3","4","5","6","7","8","9"
	};
	static const char *_S_Hemp[]={    // 湿度
		"\xe6\xb9\xbf\xe5\xba\xa6"
	};
	static const char *_S_Temp[]={    // 温度
		"\xe6\xb8\xa9\xe5\xba\xa6"
	};
	static const char *_S_Soil[]={   // 土壤
		"\xe5\x9c\x9f\xe5\xa3\xa4"
	};
	static const char *_S_Air[]={   // 空气
		"\xe7\xa9\xba\xe6\xb0\x94"
	};
	/*显示 tile 文件*/
	OrigX=LCD_GetXSize();
	OrigX=OrigX/2;
	GUI_SetFont(&GUI_Fontnongyeyun48);
	GUI_UC_SetEncodeUTF8();
	GUI_SetColor(GUI_LIGHTBLUE);
	for (i = 0; i < GUI_COUNTOF(_S_tile); i++) {
		GUI_DispStringHCenterAt(_S_tile[i],OrigX, 0);
		GUI_DispNextLine();
	}	
	/* 显示 WWW 网址 */
	GUI_SetFont(GUI_FONT_8X16);
	GUI_SetColor(GUI_DARKCYAN);
  for (i = 0; i < GUI_COUNTOF(_apStringWWW); i++) {
    GUI_DispStringHCenterAt(_apStringWWW[i], OrigX, 50);
    GUI_DispNextLine();
  }	
	showShuJu(); // 显示初始值
//  if(getInformation[0].flag==1)
//	{
//	}
//	for(i=0;i<4;i++)
//	{
//		OrigX=46+120*i;
//		OrigY=127;
//		GUI_SetFont(GUI_FONT_8X16);
//		GUI_SetColor(GUI_YELLOW);
//		GUI_GotoXY(OrigX,OrigY);
//		GUI_DispFloat(fdsa,4);
//		GUI_GotoXY(OrigX+37,OrigY);
//		GUI_DispFloat(fdsa,4);	
//		GUI_GotoXY(OrigX,OrigY+24);
//		GUI_DispFloat(fdsa,4);
//		GUI_GotoXY(OrigX+37,OrigY+24);
//		GUI_DispFloat(fdsa,4);	
//	}
//	for(i=0;i<4;i++)
//	{
//		OrigX=46+120*i;
//		OrigY=127+100;
//		GUI_SetFont(GUI_FONT_8X16);
//		GUI_SetColor(GUI_YELLOW);
//		GUI_GotoXY(OrigX,OrigY);
//		GUI_DispFloat(fdsa,4);
//		GUI_GotoXY(OrigX+37,OrigY);
//		GUI_DispFloat(fdsa,4);	
//		GUI_GotoXY(OrigX,OrigY+24);
//		GUI_DispFloat(fdsa,4);
//		GUI_GotoXY(OrigX+37,OrigY+24);
//		GUI_DispFloat(fdsa,4);
//	}
/* 显示 节点 8个 */
	GUI_SetFont(&GUI_FontwenshiduSongTi16);
	GUI_UC_SetEncodeUTF8();
	GUI_SetColor(GUI_LIGHTGREEN);
	for(j=0;j<4;j++)
	{
		OrigX=38+j*120;
		OrigY=78;
		for(i=0;i<GUI_COUNTOF(_S_note);i++)
		{
				GUI_DispStringAt(_S_note[i],OrigX,OrigY);
				
				// GUI_DispNextLine();
		}
		GUI_DispStringAt(_S_number[j],OrigX+37,OrigY);
	}
	for(j=0;j<4;j++)
	{
		OrigX=38+j*120;
		OrigY=178;
		for(i=0;i<GUI_COUNTOF(_S_note);i++)
		{
				GUI_DispStringAt(_S_note[i],OrigX,OrigY);
				
				// GUI_DispNextLine();
		}
		GUI_DispStringAt(_S_number[j+4],OrigX+37,OrigY);
	}	
	/* 写  空气  土壤 字符  */
	for(j=0;j<4;j++)
	{
		for(t=0;t<2;t++)
		{
			OrigX=7+j*120;
			OrigY=127+t*100;
			GUI_SetColor(GUI_LIGHTBLUE);
			for(i=0;i<GUI_COUNTOF(_S_Air);i++)
			{
					GUI_DispStringAt(_S_Air[i],OrigX,OrigY);		
					// GUI_DispNextLine();
			}	
			GUI_SetColor(GUI_LIGHTRED);
			for(i=0;i<GUI_COUNTOF(_S_Soil);i++)
			{
					GUI_DispStringAt(_S_Soil[i],OrigX,OrigY+23);		
					// GUI_DispNextLine();
			}	
		}
	}

/* 显示  温度   湿度   */
	for(j=0;j<4;j++)
	{
		for(t=0;t<2;t++)
		{
			OrigX=46+120*j;
		  OrigY=80+t*100;
			
			GUI_SetColor(GUI_LIGHTMAGENTA);
			for(i=0;i<GUI_COUNTOF(_S_Temp);i++)
			{
					GUI_DispStringAt(_S_Temp[i],OrigX,OrigY+23);		
					// GUI_DispNextLine();
			}	
			
			GUI_SetColor(GUI_LIGHTCYAN);
			for(i=0;i<GUI_COUNTOF(_S_Hemp);i++)
			{
					GUI_DispStringAt(_S_Hemp[i],OrigX+38,OrigY+23);		
					// GUI_DispNextLine();
			}				
		}
	}
}
