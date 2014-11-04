#ifndef _SHT_10_01_H_
#define _SHT_10_01_H_
#include "stm8s.h"
#define SDA_BAS_1  GPIOD
#define SCK_BAS_1  GPIOD
#define SCK_Pin_1  GPIO_PIN_2
#define SDA_Pin_1  GPIO_PIN_3

#define SDA_H_1()  GPIO_WriteHigh(SDA_BAS_1,SDA_Pin_1)
#define SDA_L_1()  GPIO_WriteLow(SDA_BAS_1,SDA_Pin_1)

#define SCK_H_1()  GPIO_WriteHigh(SCK_BAS_1,SCK_Pin_1)
#define SCK_L_1()  GPIO_WriteLow(SCK_BAS_1,SCK_Pin_1)
// 读取SDA数据 
#define SDA_R_1()  GPIO_ReadInputPin(SDA_BAS_1,SDA_Pin_1)
enum {TEMP1,HUMI1};
// void RCC_Config(void);
// void USART1_Config(void);
/**
  * @brief  初始化 SHT10 IO 口
  * @param  None
  * @retval None
  */
void SHT10_Config_1(void);

/**
  * @brief  配置SDA引脚为输入 
  * @param  None
  * @retval None
  */
void SHT10_SDAIn_1(void);

void SHT10_SDAOut_1(void);
void SHT10_Delay_1(void);
uint8_t SHT10_WriteByte_1(uint8_t value);
uint8_t SHT10_ReadByte_1(uint8_t Ack);
void SHT10_Start_1(void);
void SHT10_ConReset_1(void);
uint8_t SHT10_Measure_1(uint16_t* pValue, uint8_t* pCheckSum, uint8_t mode);
void SHT10_Cal_1(uint16_t Temp,uint16_t Hum, float* pTempValue,float* pHumValue);

#endif 
