#ifndef  _BSP_USART_H_
#define _BSP_USART_H_
#include"stm32f4xx.h"
#define RE_DE0  GPIO_ResetBits(GPIOE,GPIO_Pin_3)
#define RE_DE1  GPIO_SetBits(GPIOE,GPIO_Pin_3)
void Usart1_init(void);
void NVIC_Config_usart1(void);
void USART1_Puts(char * str);
#endif 
