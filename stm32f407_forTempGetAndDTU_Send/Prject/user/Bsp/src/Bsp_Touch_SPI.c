#include"Bsp_Touch_SPI.h"
#include"includes.h"
#define SPI_EN  1 
#if SPI_EN
/* 
使能硬件 SPI  
片选由软件控制
*/
void SPI2_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
  	SPI_InitTypeDef  SPI_InitStructure;

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);  //SCLK:PB13  MOSI:PB15  MISO:PB14
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB ,ENABLE); 
  	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
  	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
  	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

  	SPI_I2S_DeInit(SPI2);
  	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//全双工
  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//8位数据模式
  	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;//空闲模式下SCK为1
  	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//数据采样从第2个时间边沿开始
  	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//NSS软件管理
  	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//波特率
  	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//大端模式
  	SPI_InitStructure.SPI_CRCPolynomial = 7;//CRC多项式
  	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//主机模式
  	SPI_Init(SPI2, &SPI_InitStructure);
  	SPI_Cmd(SPI2, ENABLE);
}

void CSPin_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//TOUCH-CS:PB12
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
  	GPIO_SetBits(GPIOB, GPIO_Pin_12);//不选中
	
}

u8 SPI2_RWByte(u8 byte)
{
 	while((SPI2->SR&SPI_I2S_FLAG_TXE)==RESET);
 	SPI2->DR = byte;
 	while((SPI2->SR&SPI_I2S_FLAG_RXNE)==RESET);
 	return(SPI2->DR);
}
static void Touch_INT_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
//    EXTI_InitTypeDef EXTI_InitStructure;
//		NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,  ENABLE);  //外部中断-时钟使能 为使用下面的函数
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, GPIO_PinSource0);   //PB0
	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;   //INT:PB0  
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  
  	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; GPIO_OType_OD
	  GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);			
	
}
void Touch_Init(void)
{
		CSPin_init();
		SPI2_Init();	
		Touch_INT_Init();
}
uint16_t Touch_Read(void)
{
	uint16_t buf1,buf2;
	uint16_t buf =0;
	
	buf1 = SPI2_RWByte(0xff);
 	buf2 = SPI2_RWByte(0xff);	
	buf  = buf1;
	buf  <<=8;
	buf  |=buf2;
	buf  >>=4;
	/*
	buf +=buf1; buf <<=4;
	buf2>>=4;
	buf +=buf2; 
	*/
	return( buf ) ;
}
void Touch_WrCmd(u8 cmd)
{
	SPI2_RWByte(cmd);
}
#define  times  8
void Touch_Rd_Addata(u16 *X_Addata,u16 *Y_Addata)
{

	u16		i,j,k,x_addata[times],y_addata[times];
	       
	for(i=0;i<times;i++)					//采样4次.
	{
	  TCS_LOW();  //CS一定要在这里变化 可能与时序有关
		Touch_WrCmd( CHY ) ;
		y_addata[i] = Touch_Read() ;
    TCS_HIGH(); 

	  TCS_LOW();
		Touch_WrCmd( CHX ) ;
		x_addata[i] = Touch_Read() ;
    TCS_HIGH(); 
	}
	for(i=0;i<times;i++)
	{
    	for(j=times;j<times-1;j++)
    	{
           if(x_addata[j] > x_addata[i])
            {
                k = x_addata[j];
                x_addata[i] = x_addata[j];
                x_addata[j] = k;
            }
         }
    }

	for(i=0;i<times;i++)
	{
    	for(j=times;j<times-1;j++)
    	{
           if(y_addata[j] > y_addata[i])
            {
                k = y_addata[j];
                y_addata[i] = y_addata[j];
                y_addata[j] = k;
            }
         }
    }	
	*X_Addata=(x_addata[4] + x_addata[5]) >> 1;
	*Y_Addata=(y_addata[4] + y_addata[5]) >> 1;
}
#endif 



