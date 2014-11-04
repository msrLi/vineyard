#include"Story_datas.h"
 #include<stdlib.h>
NoteHeader note1,note2,note3,note4,note5,note6,note7,note8;


uint32_t float_size,int_size;
void Data_creat()
{


	note1.AirTempHeader=statico1[AirTemp];
	note1.AirTempHeader=statico1[AirHemp];
	note1.SoilHempHeader=statico1[SoilTemp];
	note1.SoilHempHeader=statico1[SoilHemp];
	note1.AirLenNumber=0;
	note1.SoilLenNumber=0;
	
	note2.AirTempHeader=statico2[AirTemp];
	note2.AirTempHeader=statico2[AirHemp];
	note2.SoilHempHeader=statico2[SoilTemp];
	note2.SoilHempHeader=statico2[SoilHemp];
	note2.AirLenNumber=0;
	note2.SoilLenNumber=0;
	
	note3.AirTempHeader=statico3[AirTemp];
	note3.AirTempHeader=statico3[AirHemp];
	note3.SoilHempHeader=statico3[SoilTemp];
	note3.SoilHempHeader=statico3[SoilHemp];
	note3.AirLenNumber=0;
	note3.SoilLenNumber=0;
	
	note4.AirTempHeader=statico4[AirTemp];
	note4.AirTempHeader=statico4[AirHemp];
	note4.SoilHempHeader=statico4[SoilTemp];
	note4.SoilHempHeader=statico4[SoilHemp];
	note4.AirLenNumber=0;
	note4.SoilLenNumber=0;
	
	note5.AirTempHeader=statico5[AirTemp];
	note5.AirTempHeader=statico5[AirHemp];
	note5.SoilHempHeader=statico5[SoilTemp];
	note5.SoilHempHeader=statico5[SoilHemp];
	note5.AirLenNumber=0;
	note5.SoilLenNumber=0;

	note6.AirTempHeader=statico6[AirTemp];
	note6.AirTempHeader=statico6[AirHemp];
	note6.SoilHempHeader=statico6[SoilTemp];
	note6.SoilHempHeader=statico6[SoilHemp];
	note6.AirLenNumber=0;
	note6.SoilLenNumber=0;

	  float_size=sizeof(float);
	  int_size=sizeof(int);
	
}
