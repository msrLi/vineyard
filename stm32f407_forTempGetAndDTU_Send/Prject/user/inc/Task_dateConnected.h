#ifndef _TASK_DATECONNECTED_H_
#define _TASK_DATECONNECTED_H_
#include"includes.h"
#define Max_date2  40 
typedef struct NoteInfo
{
		uint8_t flag;
		float K_tmp;
	  float K_hemo;
	  float T_tmp;
		float T_hemp;
}NoteInfo;
extern OS_SEM  Usart2RecerveSem;
extern uint8_t  rece2_buff[Max_date2];
extern uint16_t USART2_RX_STA;
extern NoteInfo getInformation[16];
void AppTaskDateConnected(void *p_arg);

#endif
