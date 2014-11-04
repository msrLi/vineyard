#ifndef _TASK_DTU_DELY_H_
#define _TASK_DTU_DELY_H_
#include"includes.h"

#define Max_date1  100 
extern OS_SEM  Usart1RecerveSem;
extern OS_SEM  Usart3RecerveSem;
extern uint8_t rece1_buff[Max_date1];
extern uint16_t USART1_RX_STA;
void AppTaskDTUDealy(void *p_arg);
#endif 
