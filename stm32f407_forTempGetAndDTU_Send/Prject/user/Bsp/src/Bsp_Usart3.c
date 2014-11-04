#include"Bsp_Usart3.h"
/* 
	 PB10 ---TX 
	 PB11---RX
*/
uint8_t Usart3RecerveData[MaxRecrveDatas];
uint16_t Usart3RecerveStart=0;
void Usart3_init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   USART_InitTypeDef USART_InitStructure;
  //EXTI_InitTypeDef EXTI_InitStructure;
  //NVIC_InitTypeDef NVIC_InitStructure;
	/* used as DTU controal  */
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);	
//	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	
   USART_DeInit(USART3);    
   // PB10,PB11 
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);    // 开启 IO 口时钟
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);      // 开始串口 3 时钟 
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);   //开启 串口3 复用时钟和配置 复用引脚 
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);   //开启 串口3 复用时钟和配置 复用引脚 
	 GPIO_StructInit(&GPIO_InitStructure);   // 恢复默认值 
	 /* 设置 PB10  ——　ｕｓａｒｔ3 TX*/
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;   // 选择复用
//   GPIO_Init(GPIOB, &GPIO_InitStructure);
//    /* 设置 PB10  ——　ｕｓａｒｔ3 RX*/
//   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
////   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//   GPIO_Init(GPIOB, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
	 
   USART_InitStructure.USART_BaudRate = 115200;  					// BPS 9600 
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;   // Bit 9 bit 
   USART_InitStructure.USART_StopBits = USART_StopBits_1;       // 停止位 1   
   USART_InitStructure.USART_Parity = USART_Parity_No;            //　无奇偶校验
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
   USART_InitStructure.USART_Mode = USART_Mode_Tx;   // alow  in and out  USART_Mode_Rx
   USART_Init(USART3, &USART_InitStructure);
	 /* set enable and set recerve interrupt   */
   USART_Cmd(USART3, ENABLE);	 
	 USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);    //中断使能
   USART_ClearFlag(USART3, USART_FLAG_TC);
	 NVIC_Config_usart3();
	 Times4_init();
}
void NVIC_Config_usart3()
{
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; //嵌套中断通道为  USART1_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级 0 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;    //响应优先级 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //中断使能
	NVIC_Init(&NVIC_InitStructure);
	
}
/*************************************************
Function: void USART3_Puts(char * str) 
Description: USART3          
Input: strings                 
Output: null                             
Return: null                               
*************************************************/
void USART3_Puts(char * str)
{
	 while (*str)
	 {
				USART_SendData(USART3, *str++);

	 /* Loop until the end of transmission */
			while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			{}
	 }
}
/* 定时器	4 定时 用于串口 3 接收*/
void Times4_init(void)    // 定时20ms
{ 
	uint32_t i;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
  RCC_ClocksTypeDef  rcc_clocks;
  RCC_GetClocksFreq(&rcc_clocks);	
	/* open clock*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	i=rcc_clocks.PCLK1_Frequency/1000000;
	TIM_TimeBaseStructure.TIM_Period=20000;
	TIM_TimeBaseStructure.TIM_Prescaler = i-1;      // 10^6 Hz   1us
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//????
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update); 
	  /* Enable TIM2 Update interrupt [TIM2??????]*/
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);  
    /* TIM2 enable counter */
//  TIM_Cmd(TIM3, ENABLE);  	
}
void ChangeTime4State(uint8_t cmd)
{
  if(cmd)
	{
		TIM4->CNT=0;         //计数器清空	 
		TIM4->CR1|=1<<0;     //使能定时器4
		TIM4->CNT=0;         //计数器清空
	}else  TIM4->CR1&=~(1<<0);     //禁止定时器4	    
}

