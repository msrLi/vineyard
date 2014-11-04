#include"BspLCDDrive.h"
/* lcd int */
//const 
#include"Asic_lib.h"   // 库函数包含
#include"Hz_lib.h"
/*
*********************************************************************************************************
*	函 数 名: Delay
*	功能说明: 延时
*	形    参: nCount 延时计数
*	返 回 值: 无
*********************************************************************************************************
*/
static void Bus_Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

void Lcd_Init(void)
{
	/* LCD  GPIO Line Init */
	BUS_dataAndAddress_config();
  /* LCD FSMC */
  LCD_FMSC();
  Bus_Delay(1000000);	  // FSMC 延时一段时间后才能使用
  GPIO_SetBits(GPIOE,GPIO_Pin_1);
	Bus_Delay(1);
	GPIO_ResetBits(GPIOE,GPIO_Pin_1);
	Bus_Delay(1);
	GPIO_SetBits(GPIOE,GPIO_Pin_1);
	Bus_Delay(1);
  COMAND=0x01;
	DATA=8;	
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{ 
    COMAND=0x03;
	DATA=x1;
    COMAND=0x02;
	DATA=y1;
    COMAND=0x07;
	DATA=x2;
    COMAND=0x06;
	DATA=y2;
	COMAND=0x0f;	 
}

void Pant(unsigned int color)
{
	int i,j;
	Address_set(0,0,MAX_W-1,MAX_H-1);
	
    for(i=0;i<MAX_W;i++)
	 {
	  for (j=0;j<MAX_H;j++)
	   	{
		   DATA=color;
	    }

	  }	
	  	
}
void Pant_pix(unsigned int x,unsigned int y,unsigned int color)
{
	Address_set(x,y,x,y);
	DATA=color;
		
}
int Red_pix(unsigned int x,unsigned int y)
{
	int data=0;
	Address_set(x,y,x,y);
	data=DATA;
// 	data=DATA;
	return data;
		
}
