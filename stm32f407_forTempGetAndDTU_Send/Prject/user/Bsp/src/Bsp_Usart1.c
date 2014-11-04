#include"Bsp_Usart1.h"
/* PB6 ---TX 
	 PB7---RX
*/

void Usart1_init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
   USART_InitTypeDef USART_InitStructure;
  //EXTI_InitTypeDef EXTI_InitStructure;
  //NVIC_InitTypeDef NVIC_InitStructure;
   USART_DeInit(USART1);    
   // PB6,PB7
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1); 
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1); 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
   //????? 
	  
   USART_InitStructure.USART_BaudRate = 115200;  					// BPS 9600 
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;   // Bit 9 bit 
   USART_InitStructure.USART_StopBits = USART_StopBits_1;       // 停止位 1   
   USART_InitStructure.USART_Parity = USART_Parity_No;            //　无奇偶校验
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   // alow  in and out 
   USART_Init(USART1, &USART_InitStructure);
	 /* set as  */
   USART_Cmd(USART1, ENABLE);
	 USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);    //中断使能
   USART_ClearFlag(USART1, USART_FLAG_TC);
	 NVIC_Config_usart1();
}
void NVIC_Config_usart1()
{
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; //嵌套中断通道为  USART1_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级 0 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;    //响应优先级 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     //中断使能
	NVIC_Init(&NVIC_InitStructure);
	
}
/*************************************************
Function: void USART1_Puts(char * str) 
Description: USART6          
Input: ???????                  
Output:?                              
Return:?                              
*************************************************/
void USART1_Puts(char * str)
{
	 while (*str)
	 {
				USART_SendData(USART1, *str++);

	 /* Loop until the end of transmission */
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			{}
	 }
}

