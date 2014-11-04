#ifndef _Bsp_Touch_SPI_h_
#define _Bsp_Touch_SPI_h_
#include "stm32f4xx.h"
#define GPIO_ADS7843_INT_VALID   !GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)

#define TCS_LOW()    	GPIO_ResetBits(GPIOB, GPIO_Pin_12)           //PB12
#define TCS_HIGH()   	GPIO_SetBits(GPIOB, GPIO_Pin_12) 
#define	CHX 	0x90 	//通道Y+的选择控制字	//0x94
#define	CHY 	0xd0	//通道X+的选择控制字	//0xD4		
void Touch_Init(void);
void CSPin_init(void);
void SPI2_Init(void);
static void Touch_INT_Init(void);
uint16_t Touch_Read(void);
void Touch_WrCmd(u8 cmd);
void Touch_Rd_Addata(u16 *X_Addata,u16 *Y_Addata);
#endif 
