#ifndef _BSPLCD_DRIVE_H_
#define _BSPLCD_DRIVE_H_
#include"stm32f4xx.h"
#include"BspLcdHal_Init.h"
#define LCD_IO_derive  1 
#if LCD_IO_derive==0
#define LOW(Port,Pin)  GPIO##Port->BSRRH = GPIO_Pin_##Pin
#define HIGH(Port,Pin)  GPIO##Port->BSRRL = GPIO_Pin_##Pin
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
#define REST0 LOW(E,1)
#define REST1 HIGH(E,1)

#define RS0 LOW(D,11)
#define RS1 HIGH(D,11)
// #define CS0  CS_base--
#define CS0 LOW(D,7)
#define CS1 HIGH(D,7)

#define WR0 LOW(D,5)
#define WR1 HIGH(D,5)

#define RD0 LOW(D,4)
#define RD1 HIGH(D,4)
#endif

#define DATA_SEND_BASE  ((uint32_t)0x60000000) // *((__IO uint16_t*) 0x60000000) volatile
//#define DA    
/*
#define DATA    (*(volatile unsigned short int *) DATA_SEND_BASE)
#define COMAND   (*(volatile unsigned short int *) (DATA_SEND_BASE | 0x20000)
*/

#define DATA    (*(volatile uint16_t *)((uint32_t)0x60020000))// 0x60020000))    //RS=1 A16=1
#define COMAND   (*(volatile uint16_t *) ((uint32_t)0x60000000))//0x60000000))  //RSA16=0

#define  writeData(x)    DATA=x
#define  writeComd(x)  	 COMAND=x
   /*************************Globe inter ***************************/
// #include"stm32f10x_conf.h"
#define MAX_W 480
#define MAX_H 272
/* color define */
#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0
//-------------------------显示颜色-------------------------------------// 
/** 
 *name:	   	 Lcd_Init
 *function:  屏幕初始化
**/
void Lcd_Init(void);
/** 
 *name:	   	 Pant
 *function:  清屏或刷屏
**/
void Pant(unsigned int color);
/** 
 *name:	   	 Pant_pix
 *function:  写数据点
**/
void Pant_pix(unsigned int x,unsigned int y,unsigned int color);
/** 
 *name:	   	 Red_pix
 *function:  读显示点
**/
int Red_pix(unsigned int x,unsigned int y);
/** 
 *name:	   	 Address_set
 *function:  设置写卡区域
**/
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void Pant_clear(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int color);
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t Color);
#endif
