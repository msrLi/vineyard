#ifndef _SHT_10_H_
#define _SHT_10_H_
#include "stm8s.h"
#define SDA_BAS  GPIOB
#define SCK_BAS  GPIOB
#define SCK_Pin  GPIO_PIN_5
#define SDA_Pin  GPIO_PIN_4

#define SDA_H()  GPIO_WriteHigh(SDA_BAS,SDA_Pin)
#define SDA_L()  GPIO_WriteLow(SDA_BAS,SDA_Pin)

#define SCK_H()  GPIO_WriteHigh(SCK_BAS,SCK_Pin)
#define SCK_L()  GPIO_WriteLow(SCK_BAS,SCK_Pin)
// 读取SDA数据 
#define SDA_R()  GPIO_ReadInputPin(SDA_BAS,SDA_Pin)
enum {TEMP,HUMI};
// void RCC_Config(void);
// void USART1_Config(void);
/**
  * @brief  初始化 SHT10 IO 口
  * @param  None
  * @retval None
  */
void SHT10_Config(void);

/**
  * @brief  配置SDA引脚为输入 
  * @param  None
  * @retval None
  */
void SHT10_SDAIn(void);

void SHT10_SDAOut(void);
void SHT10_Delay(void);
uint8_t SHT10_WriteByte(uint8_t value);
uint8_t SHT10_ReadByte(uint8_t Ack);
void SHT10_Start(void);
void SHT10_ConReset(void);
uint8_t SHT10_Measure(uint16_t* pValue, uint8_t* pCheckSum, uint8_t mode);
void SHT10_Cal(uint16_t Temp,uint16_t Hum, float* pTempValue,float* pHumValue);

#endif 
