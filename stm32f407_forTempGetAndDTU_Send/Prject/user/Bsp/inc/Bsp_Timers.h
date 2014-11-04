#ifndef _BSP_TIMES_H_
#define _BSP_TIMES_H_
#include"stm32f4xx.h"
/* 定时器	2 定时 用于串口 1 接收*/
void Times2_init(void);  
void Times3_init(void);
void ChangeTime3State(uint8_t cmd);
void ChangeTime2State(uint8_t cmd);

#endif 
 

