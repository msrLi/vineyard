#ifndef _BSP_LED_H_
#define _BSP_LED_H_
#include "stm32f4xx.h"
#include "bsp.h"
#define LED_PORT  GPIOA
#define LED_Pin  GPIO_Pin_5
//#define LEDUp_PORT  GPIOD
//#define LEDUp  GPIO_Pin_13 
//#define LEDRight_PORT  GPIOD
//#define LEDRight  GPIO_Pin_14 
//#define LEDDown_PORT  GPIOD
//#define LEDDown  GPIO_Pin_15 
void Bsp_InitLed(void);
void Trage_Led(void);
#endif
