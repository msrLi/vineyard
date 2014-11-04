#ifndef _STORY_DATAS_H_
#define _STORY_DATAS_H_
#include"stm32f4xx.h"
#define AirTemp 0
#define AirHemp 1
#define SoilTemp 2
#define SoilHemp 3
#define soil()   note##soil.SoilHempHeader=statico##soil[SoilHemp]
typedef struct 
{
		float *AirTempHeader;
	  float *AirHempHeader;
		float *SoilTempHeader;
	  float *SoilHempHeader;
	  uint16_t  AirLenNumber;
	  uint16_t SoilLenNumber;
}NoteHeader;
extern  NoteHeader note1,note2,note3,note4,note5,note6,note7,note8;

void  Data_creat(void);
#endif 
