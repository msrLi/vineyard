#ifndef _BSP_USART3_H_
#define _BSP_USART3_H_
#include"stm32f4xx.h"
#define MaxRecrveDatas  200
extern uint8_t Usart3RecerveData[MaxRecrveDatas];
extern uint16_t Usart3RecerveStart;
void Usart3_init(void);
void NVIC_Config_usart3(void);
void USART3_Puts(char * str);
void Times4_init(void);    // ¶¨Ê±20ms
void ChangeTime4State(uint8_t cmd);
#endif 
