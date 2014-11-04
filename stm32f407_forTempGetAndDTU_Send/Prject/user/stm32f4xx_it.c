/**
  ******************************************************************************
  * @file    Audio_playback_and_record/src/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    28-October-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include"stm32f4xx_it.h"
#include"Bsp_Led.h"
//#include "stm32f4xx_usart.h"

/** @addtogroup STM32F4-Discovery_Audio_Player_Recorder
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

void USART1_IRQHandler(void)
{	
	OS_ERR     err;
	uint16_t buff;
  OSIntEnter();  // 通知ucos进入中断 
	buff=USART_ReceiveData(USART1);
	if(USART1_RX_STA<Max_date1)
	{
		TIM2->CNT=0;
		if(USART1_RX_STA==0)  // 数据接收开始标志 
		{
			/* 打开定时 2 作为一个整体传输 */ 
			ChangeTime2State(1);
		}
		rece1_buff[USART1_RX_STA++]=buff;
	}else
	{
		USART1_RX_STA|=1<<15;					//强制标记接收完成
		rece1_buff[Max_date1-1]=0;  // 结束标志
		OSSemPost((OS_SEM *)&Usart1RecerveSem,
						 (OS_OPT  )OS_OPT_POST_ALL,
						 (OS_ERR *)&err);	
	}
	 USART_ClearFlag(USART1,USART_FLAG_RXNE);
	 OSIntExit();    // 通知ucos 退出中断
}
void USART2_IRQHandler(void)
{
	OS_ERR     err;
	uint16_t buff;
	OSIntEnter();  // 通知ucos进入中断 
	buff=USART_ReceiveData(USART2);
	if(USART2_RX_STA<Max_date2)
	{
		TIM3->CNT=0;
		if(USART2_RX_STA==0)  // 数据接收开始标志 
		{
			/* 打开定时 2 作为一个整体传输 */ 
			ChangeTime3State(1);
		}
		rece2_buff[USART2_RX_STA++]=buff;
	}else
	{
		USART2_RX_STA|=1<<15;					//强制标记接收完成
		rece2_buff[Max_date2-1]=0;  // 结束标志
		OSSemPost((OS_SEM *)&Usart2RecerveSem,
						 (OS_OPT  )OS_OPT_POST_ALL,
						 (OS_ERR *)&err);	
	}
	 USART_ClearFlag(USART2,USART_FLAG_RXNE);
	 OSIntExit();    // 通知ucos 退出中断
}
/*
extern uint8_t Usart3RecerveData[MaxRecrveDatas];
extern uint16_t Usart3RecerveStart;
*/
void USART3_IRQHandler(void)
{
	OS_ERR     err;
	uint16_t buff;
	OSIntEnter();  // 通知ucos进入中断 
  buff = USART_ReceiveData(USART3);
	if(Usart3RecerveStart<MaxRecrveDatas-1)    // 判断收取到数据量是否在缓冲数量范围之内
	{
		TIM3->CNT=0;
		if(Usart3RecerveStart==0)
		{
			ChangeTime4State(1);			
		}
		Usart3RecerveData[Usart3RecerveStart++]=buff;
	}else{   // 超出最大接受数量
		Usart3RecerveStart |= 0x01<<15;
		Usart3RecerveData[MaxRecrveDatas-1]=0;   // 添加 结束符
		USART_ClearFlag(USART3,USART_FLAG_RXNE);
		OSSemPost((OS_SEM *)&Usart3RecerveSem,
						 (OS_OPT  )OS_OPT_POST_ALL,
						 (OS_ERR *)&err);			
	}
	USART_ClearFlag(USART3,USART_FLAG_RXNE);
	OSIntExit();    // 通知ucos 退出中断
}

void TIM2_IRQHandler(void)
{
	OS_ERR     err;
	OSIntEnter();  // 通知ucos进入中断 
	if(TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET )
	{	
		ChangeTime2State(0); // 结束定时器2计数 
		rece1_buff[USART1_RX_STA]=0;
		USART1_RX_STA|=1<<15;					//强制标记接收完成
		OSSemPost((OS_SEM *)&Usart1RecerveSem,
						 (OS_OPT  )OS_OPT_POST_ALL,
						 (OS_ERR *)&err);			
	}
	TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);	//clear interrupt flags
	OSIntExit();    // 通知ucos 退出中断
}
void TIM3_IRQHandler(void)
{
	OS_ERR     err;
	OSIntEnter();  // 通知ucos进入中断 
	if(TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET )
	{
		ChangeTime3State(0); // 结束定时器2计数 
		rece2_buff[USART2_RX_STA]=0;
		USART2_RX_STA|=1<<15;					//强制标记接收完成
		OSSemPost((OS_SEM *)&Usart2RecerveSem,
						 (OS_OPT  )OS_OPT_POST_ALL,
						 (OS_ERR *)&err);
	}
	TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);	//clear interrupt flags
	OSIntExit();    // 通知ucos 退出中断
}

void TIM4_IRQHandler(void)
{
	OS_ERR     err;
	OSIntEnter();  // 通知ucos进入中断 
	if(TIM_GetITStatus(TIM4 , TIM_IT_Update) != RESET )   // 定时器4 定时 中断 
	{
		ChangeTime4State(0); // 结束定时器4计数 
		Usart3RecerveData[Usart3RecerveStart]=0;
		Usart3RecerveStart |= 0x01<<15;
		OSSemPost((OS_SEM *)&Usart3RecerveSem,
						 (OS_OPT  )OS_OPT_POST_ALL,
						 (OS_ERR *)&err);		
	}
	TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update);	//clear interrupt flags
	OSIntExit();    // 通知ucos 退出中断
}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

}


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/
/**
  * @brief  This function handles External line 1 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{

}

/**
  * @brief  This function handles TIM4 global interrupt request.
  * @param  None
  * @retval None
  */


#if defined MEDIA_USB_KEY
/**
  * @brief  EXTI0_IRQHandler
  *         This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{

}


/**
  * @brief  This function handles TIM2 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
  // USB_OTG_BSP_TimerIRQ();
}


/**
  * @brief  This function handles USB-On-The-Go FS global interrupt request.
  * @param  None
  * @retval None
  */
void OTG_FS_IRQHandler(void)
{
  // USBH_OTG_ISR_Handler(&USB_OTG_Core);
}
#endif /* MEDIA_USB_KEY */

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @}
  */ 
  
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
