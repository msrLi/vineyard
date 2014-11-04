#ifndef _EXCHANGEDATA_H_
#define _EXCHANGEDATA_H_
// #include"headerAllConfig.h"
#include "stm32f4xx.h"
#include<string.h>
#include<math.h>  
#include<assert.h> 
/* 整行转换成  字符串行  */ 
char* myitoa(int num,char*str,int radix);
char *my_ftoa(double number,int ndigit,char *buf);

/*  字符串转整形 */ 
int my_atoi(const char * str);

/*  字符串转换成double型数据 */
double myatof(char *s);
#endif 

