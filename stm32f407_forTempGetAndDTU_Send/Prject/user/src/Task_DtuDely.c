#include"Task_DtuDely.h"
#define MaxSendBuffLen  400      // 串口发送 最大缓冲数据数量
OS_SEM  Usart1RecerveSem;       // 串口1  信号量 
OS_SEM  Usart3RecerveSem;       //  串口3 同步信号量
uint8_t rece1_buff[Max_date1];  // 串口数据缓冲 
uint16_t USART1_RX_STA=0;     //串口接收结束标志和 接收数量存放位置
uint8_t DTUOkFlag=0;          // DTU 状态 指示标志 
const char PATCH[]={"lhh/index.php?c=main&a=insert"};   //路径名
const char FACTORY[]={"&fat=2"};     // 厂房号 
const char DEVICE[]={"&dev"};        // 设备 标志
char SendDataBuff[MaxSendBuffLen];
/* 
extern uint8_t Usart3RecerveData[MaxRecrveDatas];
extern uint16_t Usart3RecerveStart;
*/
void SendInfomationToInternet(void)
{
	uint8_t i;
	
	char SendTenpBuffI[10];
	strcpy(SendDataBuff,PATCH);    // f复制 Patch内容到 SendDataBuff中 
	strcat(SendDataBuff,FACTORY);
	for(i=0;i<8;i++)
	{
		strcat(SendDataBuff,DEVICE);
		strcat(SendDataBuff,"[");
		myitoa(i+1,SendTenpBuffI,10);    //将 i+1 转换成 字符串形式 十进制形式转换 
		strcat(SendDataBuff,SendTenpBuffI);
		strcat(SendDataBuff,"]=");
//		if(getInformation[i].flag!=1)
//		{
//			strcat(SendDataBuff,"*;*;*;*");
//		}else{
			if(getInformation[i].T_tmp==0 && getInformation[i].T_hemp == 0)
			{
				strcat(SendDataBuff,"*;*;");
			}else{
				my_ftoa(getInformation[i].T_tmp,1,SendTenpBuffI);
				strcat(SendDataBuff,SendTenpBuffI);
				strcat(SendDataBuff,";");
				my_ftoa(getInformation[i].T_hemp,1,SendTenpBuffI);
				strcat(SendDataBuff,SendTenpBuffI);
				strcat(SendDataBuff,";");
			}
			if(getInformation[i].K_tmp == 0 && getInformation[i].K_hemo == 0)
			{
				strcat(SendDataBuff,"*;*");
			}else{
				my_ftoa(getInformation[i].K_tmp,1,SendTenpBuffI);
				strcat(SendDataBuff,SendTenpBuffI);
				strcat(SendDataBuff,";");
				my_ftoa(getInformation[i].K_hemo,1,SendTenpBuffI);
				strcat(SendDataBuff,SendTenpBuffI);
			}				
//		}
	}
	strcat(SendDataBuff,"\r\n");
	Usart3RecerveStart=0;	
//	GPIO_SetBits(GPIOC,GPIO_Pin_1);  //set DTU as High
	USART3_Puts(SendDataBuff);
	USART1_Puts(SendDataBuff);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
}
void sendHttpData(void)
{
	uint32_t time_delays;
	char *strx=0;
//	uint32_t i;
	static uint16_t countdatas=0;
	OS_ERR     err;
	switch(DTUOkFlag)
	{
		case 0:
		  SendInfomationToInternet();   //发数据  
			time_delays=(uint32_t) 15000;  // 等待10s  等待Jump
			break;
		case 1:
			time_delays=(uint32_t) 5000;   // 4s 等待 时间     
			break;
		case 2:
			time_delays=(uint32_t) 5000;   // 4s 等待 时间     
			break;
		case 3:
			time_delays=(uint32_t) 500;  // 等待500ms
			break;
		case 4:
			SendInfomationToInternet();
			time_delays=(uint32_t) 15000;  // 等待  15 s
			break;
		case 5:
		default:
			SendInfomationToInternet();
			time_delays=(uint32_t) 10000;  // 等待500ms
			break;			
	}
	OSSemPend((OS_SEM *)&Usart3RecerveSem,
				(OS_TICK )time_delays,
				(OS_OPT  )OS_OPT_PEND_BLOCKING,
				(CPU_TS  )0,
				(OS_ERR *)&err); 
	countdatas++;
	if(err==OS_ERR_NONE)    // 正常返回
	{
	   USART1_Puts((char *)Usart3RecerveData);		
		if(Usart3RecerveStart&(0x01<<15))
		{
			strx=strstr((const char *)Usart3RecerveData,(const char *)"ok");	
			if(strx!=0)
			{
				countdatas=4;	
				Usart3RecerveStart=0;
				return;    //返回 
			}
			strx=strstr((const char *)Usart3RecerveData,(const char *)"Jump");
			if(strx!=0)
			{
				DTUOkFlag=1;
				Usart3RecerveStart=0;
				return;
			}
			strx=strstr((const char *)Usart3RecerveData,(const char *)"USR");
			if(strx!=0)
			{
				DTUOkFlag=2;
				Usart3RecerveStart=0;
				return;
			}
			strx=strstr((const char *)Usart3RecerveData,(const char *)"CSIM");
			if(strx!=0)
			{
				DTUOkFlag=3;
				Usart3RecerveStart=0;
				return;
			}
			strx=strstr((const char *)Usart3RecerveData,(const char *)"OK");
			if(strx!=0)
			{
				DTUOkFlag=4;
				Usart3RecerveStart=0;
				return;
			}
			strx=strstr((const char *)Usart3RecerveData,(const char *)"UNKNOW");
			if(strx!=0)// UNKNOW
			{
				DTUOkFlag=4;
				Usart3RecerveStart=0;
				return;
			}
		  Usart3RecerveStart=0;
		}			
	}
	if(err==OS_ERR_TIMEOUT)     // 时间延时 
	{
		
	}
	if(err==OS_ERR_OBJ_TYPE)    //  没有 检测到 直线信号量 
	{
		OSSemCreate((OS_SEM    *)&Usart3RecerveSem,
								(CPU_CHAR  *)"Usart3RecerveSem",
								(OS_SEM_CTR )0,
								(OS_ERR    *)&err);				
	}	
	Usart3RecerveStart=0;	
	
}
float my_text001=63.213154;
char My_temps[10];

void AppTaskDTUDealy(void *p_arg)
{
	OS_ERR     err;

//	GPIO_InitTypeDef GPIO_InitStructure;
  (void) p_arg;
	  
	/* 创建 信号量 用与同步两个进程 */
	// 用于同步  cn=0;
	OSSemCreate((OS_SEM    *)&Usart3RecerveSem,
							(CPU_CHAR  *)"Usart3RecerveSem",
							(OS_SEM_CTR )0,
							(OS_ERR    *)&err);	

	// Usart3_init();
	Usart3RecerveStart=0;
	while(1)
	{
    sendHttpData();		
		 //开启中断 
	}
}

