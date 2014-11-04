#include"BspLCDDrive.h"
/* lcd int */
//const 
#include"includes.h"
#include"Asic_lib.h"   // 库函数包含
#include"Hz_lib.h"
#include"Font.h"
uint16_t BACK_COLOR, POINT_COLOR;   //背景色，画笔色		
/*
*********************************************************************************************************
*	函 数 名: Delay
*	功能说明: 延时
*	形    参: nCount 延时计数
*	返 回 值: 无
*********************************************************************************************************
*/
uint32_t dely_ms;
static void Bus_Delay(__IO uint32_t nCount)
{
	for(; nCount != 0; nCount--);
}
#if LCD_IO_derive
void Lcd_Init(																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									void)
{
	/* LCD  GPIO Line Init */
	BUS_dataAndAddress_config();
  /* LCD FSMC */
  LCD_FMSC();	
// 	OSTimeDlyHMSM((CPU_INT16U) 0u,
//                 (CPU_INT16U) 0u,
//                  (CPU_INT16U) 0,
//                  (CPU_INT32U) 20,
//                  (OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
//                  (OS_ERR   *)&err);
  Bus_Delay(6000000);	  // FSMC 延时一段时间后才能使用
	GPIO_ResetBits(GPIOD,GPIO_Pin_13);
	Bus_Delay(480000);
// 	OSTimeDlyHMSM((CPU_INT16U) 0u,
//                 (CPU_INT16U) 0u,
//                  (CPU_INT16U) 0,
//                  (CPU_INT32U) 20,
//                  (OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
//                  (OS_ERR   *)&err);
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
// 	OSTimeDlyHMSM((CPU_INT16U) 0u,
//                 (CPU_INT16U) 0u,
//                  (CPU_INT16U) 0,
//                  (CPU_INT32U) 20,
//                  (OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
//                  (OS_ERR   *)&err);
	Bus_Delay(480000);
  COMAND=0x01;
	DATA=16;	
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
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t Color)
{          
	u16 i,j; 
	Address_set(xsta,ysta,xend,yend);      //设置光标位置 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)
		{

		  DATA=Color;

		}
		  // LCD_WR_DATA(color);//设置光标位置 	    
	} 					  	    
} 
/* 画线函数 */
void DrawLine(uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2,uint16_t Color)
{
  uint16_t t;
	int16_t xerr=0,yerr=0,delta_x,delta_y,distance;
	int16_t incx,incy,uRow,uCol;
	delta_x=x2-x1; // 计算 坐标增量 
	delta_y=y2-y1;
	uRow=x1;     // 行开始  坐标
	uCol=y1;    // 列开始  坐标
	if(delta_x>0) incx=1; //设置单步方向
	else if(delta_x==0) incx=0; //垂直线
	else{
		incx=-1;
		delta_y=-delta_y;	
	}
	
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{
		incy=-1;
		delta_y=-delta_y;
	} 

	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
//		LCD_DrawPoint(uRow,uCol);//画点 
	  Address_set(uRow,uCol,uRow,uCol);

	  DATA=Color;

		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	} 	
}
//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"
//mode:叠加方式(1)还是非叠加方式(0)
//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"

//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t mode)
{
    uint8_t temp;
    uint8_t pos,t;
	  uint16_t x0=x;
	  uint16_t colortemp=POINT_COLOR;      
    if(x>800-16||y>480-16)return;	    
	//设置窗口		   
	num=num-' ';//得到偏移后的值
	Address_set(x,y,x+8-1,y+16-1);      //设置光标位置 
	if(!mode) //非叠加方式
	{
		for(pos=0;pos<16;pos++)
		{ 
			temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				// LCD_WR_DATA(POINT_COLOR);

				DATA=POINT_COLOR;	
				
				temp>>=1; 
				x++;
		    }
			x=x0;
			y++;
		}	
	}else//叠加方式
	{
		for(pos=0;pos<16;pos++)
		{
		   temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
			 for(t=0;t<8;t++)
		   {                 
		        if(temp&0x01)Pant_pix(x+t,y+pos,POINT_COLOR);//画一个点     
		        temp>>=1; 
		   }
		}
	}
	POINT_COLOR=colortemp;	    	   	 	  
}  
//显示字符串
//x,y:起点坐标  
//*p:字符串起始地址
//用16字体
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p)
{         
    while(*p!='\0')
    {       
        if(x>800-16){x=0;y+=16;}
        if(y>480-16){y=x=0;Pant(Red);}
        LCD_ShowChar(x,y,*p,0);
        x+=8;
        p++;
    }  
}
#else
/*
	PD0/FSMC_D2
	PD1/FSMC_D3
	PD4/FSMC_NOE		--- 读控制信号，OE = Output Enable ， N 表示低有效
	PD5/FSMC_NWE		--- 写控制信号，WE = Output Enable ， N 表示低有效
	PD8/FSMC_D13
	PD9/FSMC_D14
	PD10/FSMC_D15
	PD11/FSMC_A16		--- 地址 RS
	PD14/FSMC_D0
	PD15/FSMC_D1


	PE7/FSMC_D4
	PE8/FSMC_D5
	PE9/FSMC_D6
	PE10/FSMC_D7
	PE11/FSMC_D8
	PE12/FSMC_D9
	PE13/FSMC_D10
	PE14/FSMC_D11
	PE15/FSMC_D12

	PD7/FSMC_NE1		--- 主片选（TFT）
  PE1 --> LCD_reset 
*/
void IO_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 
	| GPIO_Pin_8 | GPIO_Pin_9
	| GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // GPIO_Mode_AF
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_7 | GPIO_Pin_8	 | GPIO_Pin_9 | GPIO_Pin_10
	| GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOE,GPIO_Pin_1);
	// GPIOD->BSRRL = GPIO_Pin_7;
}
void LCD_Writ_Bus(uint16_t dates)   //并行数据写入函数
{
 //	uint8_t i;
//	HIGH(D,4);
	  if(dates&0x0001) HIGH(D,14); else LOW(D,14); 
		if(dates&0x0002) HIGH(D,15); else LOW(D,15);  //D1 
		if(dates&0x0004) HIGH(D,0); else LOW(D,0);  //D2
		if(dates&0x0008) HIGH(D,1); else LOW(D,1);  //D3
		
		if(dates&0x0010) HIGH(E,7); else  LOW(E,7);  //D4
		if(dates&0x0020) HIGH(E,8); else  LOW(E,8);  //D5
		if(dates&0x0040) HIGH(E,9);  else LOW(E,9);  //D6
		if(dates&0x0080) HIGH(E,10); else LOW(E,10); //D7
		
		if(dates&0x0100) HIGH(E,11); else LOW(E,11); //D8
		if(dates&0x0200) HIGH(E,12); else LOW(E,12); //D9
		if(dates&0x0400) HIGH(E,13); else LOW(E,13); //D10
		if(dates&0x0800) HIGH(E,14); else LOW(E,14); //D11
		
		if(dates&0x1000) HIGH(E,15); else LOW(E,15); //D12
		if(dates&0x2000) HIGH(D,8);  else LOW(D,8);  //D13
		if(dates&0x4000) HIGH(D,9);  else LOW(D,9);  //D14
		if(dates&0x8000) HIGH(D,10); else LOW(D,10); //D15
    WR0;
		Bus_Delay(1000);
	  WR1;
}
void LCD_WR_REG(uint16_t da)	 
{	
		RS0;  // RS=0
	  LCD_Writ_Bus(da);
//	LCD_Writ_Bus(da>>8,da);
}
void LCD_WR_DATA(uint16_t da)
{
  RS1;
	LCD_Writ_Bus(da);
}	 
void Lcd_Init(																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									void)
{

	/* LCD  GPIO Line Init */

//	BUS_dataAndAddress_config();
//  /* LCD FSMC */
//  LCD_FMSC();	
  IO_init();
  Bus_Delay(6000000);	  // FSMC 延时一段时间后才能使用
	LOW(E,1);
	Bus_Delay(600000);
	// GPIO_SetBits(GPIOE,GPIO_Pin_1);
	HIGH(E,1);
	Bus_Delay(600000);
	CS0;  // CS =0 
	LCD_WR_REG(0x01); //打开背光	
	LCD_WR_DATA(16); 
	
//  COMAND=0x01;
//	DATA=15;	
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
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t Color)
{          
	u16 i,j; 
	Address_set(xsta,ysta,xend,yend);      //设置光标位置 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)
		{

		  DATA=Color;

		}
		  // LCD_WR_DATA(color);//设置光标位置 	    
	} 					  	    
} 
/* 画线函数 */
void DrawLine(uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2,uint16_t Color)
{
  uint16_t t;
	int16_t xerr=0,yerr=0,delta_x,delta_y,distance;
	int16_t incx,incy,uRow,uCol;
	delta_x=x2-x1; // 计算 坐标增量 
	delta_y=y2-y1;
	uRow=x1;     // 行开始  坐标
	uCol=y1;    // 列开始  坐标
	if(delta_x>0) incx=1; //设置单步方向
	else if(delta_x==0) incx=0; //垂直线
	else{
		incx=-1;
		delta_y=-delta_y;	
	}
	
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{
		incy=-1;
		delta_y=-delta_y;
	} 

	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
//		LCD_DrawPoint(uRow,uCol);//画点 
	  Address_set(uRow,uCol,uRow,uCol);

	  DATA=Color;

		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	} 	
}
//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"
//mode:叠加方式(1)还是非叠加方式(0)
//在指定位置显示一个字符

//num:要显示的字符:" "--->"~"

//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t mode)
{
    uint8_t temp;
    uint8_t pos,t;
	  uint16_t x0=x;
	  uint16_t colortemp=POINT_COLOR;      
    if(x>800-16||y>480-16)return;	    
	//设置窗口		   
	num=num-' ';//得到偏移后的值
	Address_set(x,y,x+8-1,y+16-1);      //设置光标位置 
	if(!mode) //非叠加方式
	{
		for(pos=0;pos<16;pos++)
		{ 
			temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				// LCD_WR_DATA(POINT_COLOR);

				DATA=POINT_COLOR;	
				
				temp>>=1; 
				x++;
		    }
			x=x0;
			y++;
		}	
	}else//叠加方式
	{
		for(pos=0;pos<16;pos++)
		{
		   temp=asc2_1608[(u16)num*16+pos];		 //调用1608字体
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)Pant_pix(x+t,y+pos,POINT_COLOR);//画一个点     
		        temp>>=1; 
		    }
		}
	}
	POINT_COLOR=colortemp;	    	   	 	  
}  
//显示字符串
//x,y:起点坐标  
//*p:字符串起始地址
//用16字体
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p)
{         
    while(*p!='\0')
    {       
        if(x>800-16){x=0;y+=16;}
        if(y>480-16){y=x=0;Pant(Red);}
        LCD_ShowChar(x,y,*p,0);
        x+=8;
        p++;
    }  
}
#endif 

