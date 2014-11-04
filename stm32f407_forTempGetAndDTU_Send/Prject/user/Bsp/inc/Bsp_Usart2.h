#ifndef _BSP_USART2_H_
#define _BSP_USART2_H_
#include"stm32f4xx.h"

void Usart2_init(void);
void Usart2_sendChar(uint16_t buff);
void Usart2_sendString(uint16_t * BuffAdd);
#endif 
