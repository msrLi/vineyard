#include"BspLcdHal_Init.h"

/* 最终 LCD复位 改成 D12*/
void LCD_FMSC()
{
	FSMC_NORSRAMInitTypeDef  init;
	FSMC_NORSRAMTimingInitTypeDef  timingWrite;
//	FSMC_NORSRAMTimingInitTypeDef  timingRead;
	/*-- FSMC Configuration ------------------------------------------------------*/
	/*----------------------- SRAM Bank 1 ----------------------------------------*/
	/* FSMC_Bank1_NORSRAM4 configuration */
	/* 摄像头DMA麻点，需设置 4 0 5 2 0 0 */
//	timingWrite.FSMC_AddressSetupTime = 10;   // 地址建立时间
//	timingWrite.FSMC_AddressHoldTime = 0;    // 地址持续时间
//	timingWrite.FSMC_DataSetupTime = 35;     // 数据建立时间  // 35
//	timingWrite.FSMC_BusTurnAroundDuration = 4;
//	timingWrite.FSMC_CLKDivision = 0;        // 时钟分频系数
//	timingWrite.FSMC_DataLatency = 0;        // 数据延时 50
//	timingWrite.FSMC_AccessMode = FSMC_AccessMode_B;
	timingWrite.FSMC_AddressSetupTime = 4;   // 地址建立时间
	timingWrite.FSMC_AddressHoldTime = 0;    // 地址持续时间
	timingWrite.FSMC_DataSetupTime = 38;     // 数据建立时间  // 38
	timingWrite.FSMC_BusTurnAroundDuration = 3;  // 4 
	timingWrite.FSMC_CLKDivision = 0;        // 时钟分频系数
	timingWrite.FSMC_DataLatency = 0;        // 数据延时 50
	timingWrite.FSMC_AccessMode = FSMC_AccessMode_B;
//	
//	timingRead.FSMC_AddressSetupTime = 4;   // 5
//	timingRead.FSMC_AddressHoldTime = 0;
//	timingRead.FSMC_DataSetupTime = 40;   //53
//	timingRead.FSMC_BusTurnAroundDuration = 3;
//	timingRead.FSMC_CLKDivision = 0;
//	timingRead.FSMC_DataLatency = 0;
//	timingRead.FSMC_AccessMode = FSMC_AccessMode_B;   // 访问模式 
//	timingRead.FSMC_AddressSetupTime = 8;   // 5
//	timingRead.FSMC_AddressHoldTime = 1;
//	timingRead.FSMC_DataSetupTime = 8;   //53
//	timingRead.FSMC_BusTurnAroundDuration = 0;
//	timingRead.FSMC_CLKDivision = 0;
//	timingRead.FSMC_DataLatency = 0;
//	timingRead.FSMC_AccessMode = FSMC_AccessMode_B;   // 访问模式 
	/*
	 LCD configured as follow:
	    - Data/Address MUX = Disable
	    - Memory Type = SRAM
	    - Data Width = 16bit
	    - Write Operation = Enable
	    - Extended Mode = Enable
	    - Asynchronous Wait = Disable
	*/
	init.FSMC_Bank = FSMC_Bank1_NORSRAM1;
	init.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	init.FSMC_MemoryType =  FSMC_MemoryType_NOR;  
	init.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	init.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	init.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;	/* 注意旧库无这个成员 */
	init.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	init.FSMC_WrapMode = FSMC_WrapMode_Disable;
	init.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	init.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	init.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	init.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	init.FSMC_WriteBurst = FSMC_WriteBurst_Disable;

	init.FSMC_ReadWriteTimingStruct = &timingWrite;
	init.FSMC_WriteTimingStruct = &timingWrite;

	FSMC_NORSRAMInit(&init);

	/* - BANK 1 (of NOR/SRAM Bank 1~4) is enabled */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
	
//      FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
//      FSMC_NORSRAMTimingInitTypeDef  p;
//    
//      RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);
//    
//      /* FSMC_Bank1_NORSRAM1 timing configuration */
//      p.FSMC_AddressSetupTime = 0;/*地址建立时间期限*/                                            
//      p.FSMC_AddressHoldTime = 0;/*地址的持续时间*/
//      p.FSMC_DataSetupTime = 1;/*设定数据时间期限*/
//      p.FSMC_BusTurnAroundDuration = 0x00;/*总线转向时间*/
//      p.FSMC_CLKDivision = 0x00;/*CLK时钟输出信号的HCLK周期数表示时间???*/
//      p.FSMC_DataLatency = 0x00;/*指定在获得第一个数据前的时钟周期*/
//      p.FSMC_AccessMode = FSMC_AccessMode_B;
//    
//      FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;/*指定的FSMC块*/
//      FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; /*地址和数据值不复用的数据总线*/                                         
//      FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;     /*外部存储器的类型*/
//      FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;/*数据宽度*/
//      FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;/* 禁用突发访问模式*/
//      FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;/*指定等待信号的极性*/
//      FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;/*Enables or disables the Wrapped burst access mode for Flash*/
//      FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
//      FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;/*启用指定的FSMC块的写操作*/
//      FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
//      FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;/*扩展模式*/
//      FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;/*禁用写突发操作*/
//      FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
//      FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;	     
//      FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);   
//      /* Enable FSMC Bank1_SRAM Bank */
//      FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}
/*
	显示屏 连接方式 

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
  PD13 --> LCD_reset 
//	PC3/TP_INT			--- 触摸芯片中断 （对于RA8875屏，是RA8875输出的中断)  本例程未使用硬件中断

//	---- 下面是 TFT LCD接口其他信号 （FSMC模式不使用）----
//	PD3/LCD_BUSY		--- 触摸芯片忙       （RA8875屏是RA8875芯片的忙信号)
//	PF6/LCD_PWM			--- LCD背光PWM控制  （RA8875屏无需此脚，背光由RA8875控制)

//	PI10/TP_NCS			--- 触摸芯片的片选		(RA8875屏无需SPI接口触摸芯片）
//	PB3/SPI3_SCK		--- 触摸芯片SPI时钟		(RA8875屏无需SPI接口触摸芯片）
//	PB4/SPI3_MISO		--- 触摸芯片SPI数据线MISO(RA8875屏无需SPI接口触摸芯片）
//	PB5/SPI3_MOSI		--- 触摸芯片SPI数据线MOSI(RA8875屏无需SPI接口触摸芯片）
*/
void BUS_dataAndAddress_config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* 使能FSMC时钟 */
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE , ENABLE);
	/* 设置 PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
	 PD.10(D15), PD.14(D0), PD.15(D1) 为复用推挽输出 */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);   // F_D2
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);   // F_D3
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);   // F_NOE
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);   // F_NWR
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);   // F_D13
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);   // F_D14
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10,GPIO_AF_FSMC);   // F_D15
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);  // F_D0
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);  // F_D1

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 |
	                            GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 |
	                            GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	/* 设置 PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
	 PE.14(D11), PE.15(D12) 为复用推挽输出 */

//	GPIO_PinAFConfig(GPIOE, GPIO_PinSource4 , GPIO_AF_FSMC);
//	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5 , GPIO_AF_FSMC);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);       // F_D4
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);       // F_D5
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);			 // F_D6
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);			 // F_D7
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);			 // F_D8
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);			 // F_D9
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);			 // F_D10
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);			 // F_D11
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);			 // F_D12

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
	                            GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
	                            GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/* 设置 PD.11(A16 (RS))  为复用推挽输出 */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);    // F_A16

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* 设置 PD7 (LCD/CS)) 为复用推挽输出 */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);     // F_NE1

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
/* 复位管脚 */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOD, GPIO_Pin_7);			//CS=1 
	GPIO_SetBits(GPIOD, GPIO_Pin_11);			//RS=1
	GPIO_SetBits(GPIOD, GPIO_Pin_8| GPIO_Pin_9 |GPIO_Pin_10);  	 
	GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
	GPIO_SetBits(GPIOD, GPIO_Pin_13);			//RESET=1
	GPIO_SetBits(GPIOD, GPIO_Pin_4);		    //RD=1
	GPIO_SetBits(GPIOD, GPIO_Pin_5);			//WR=1
}

