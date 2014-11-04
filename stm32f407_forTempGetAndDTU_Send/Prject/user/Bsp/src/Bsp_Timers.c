#include"Bsp_Timers.h"
/* 定时器	2 定时 用于串口 1 接收*/
void Times2_init(void)    // 定时20ms
{ 
	uint32_t i;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  RCC_ClocksTypeDef  rcc_clocks;
  RCC_GetClocksFreq(&rcc_clocks);	
	/* open clock*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	i=rcc_clocks.PCLK1_Frequency/1000000;
	TIM_TimeBaseStructure.TIM_Period=30000;
	TIM_TimeBaseStructure.TIM_Prescaler = i-1;      // 10^6 Hz   1us
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//????
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); 
	  /* Enable TIM2 Update interrupt [TIM2??????]*/
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  
    /* TIM2 enable counter */
//  TIM_Cmd(TIM2, ENABLE);  	
}
/* 定时器	3 定时 用于串口 2 接收*/
void Times3_init(void)    // 定时20ms
{ 
	uint32_t i;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  RCC_ClocksTypeDef  rcc_clocks;
  RCC_GetClocksFreq(&rcc_clocks);	
	/* open clock*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	i=rcc_clocks.PCLK1_Frequency/1000000;
	TIM_TimeBaseStructure.TIM_Period=20010;
	TIM_TimeBaseStructure.TIM_Prescaler = i-1;      // 10^6 Hz   1us
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//????
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update); 
	  /* Enable TIM2 Update interrupt [TIM2??????]*/
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);  
    /* TIM2 enable counter */
//  TIM_Cmd(TIM3, ENABLE);  	
}
void ChangeTime2State(uint8_t cmd)
{
  if(cmd)
	{
		TIM2->CNT=0;         //计数器清空	 
		TIM2->CR1|=1<<0;     //使能定时器4
		TIM2->CNT=0;         //计数器清空
	}else  TIM2->CR1&=~(1<<0);     //禁止定时器4	    
}
void ChangeTime3State(uint8_t cmd)
{
  if(cmd)
	{
		TIM3->CNT=0;         //计数器清空	 
		TIM3->CR1|=1<<0;     //使能定时器4
		TIM3->CNT=0;         //计数器清空
	}else  TIM3->CR1&=~(1<<0);     //禁止定时器4	    
}


