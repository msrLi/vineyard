#include"Task_dateConnected.h"
#define Base  2
#define SAVEDATATIME    360000
#define  time_out_dely  300
OS_SEM  Usart2RecerveSem;
uint8_t  rece2_buff[Max_date2];
uint16_t USART2_RX_STA;
float Tempss;    //story  temps 
uint16_t tempval;   // story temp for none exchange 
float Hempss;       	//story hemp
uint16_t hempval;			//story hemp for none exchange 
NoteInfo getInformation[16];
uint8_t DrawingDataSave[8][4][200];
uint8_t numbersDrawing=0;
OS_TICK clk1,clkOld;
uint8_t flag_clock=0;
float tempHempAndTem[8][4]; 
float lastTempHemp[8][4]; 
float absFloat(float buffstmo)
{
	if(buffstmo>=0)
	  return buffstmo;
	else 
		return (-buffstmo);
}
/** 
	*	作用：计算温度湿度数据
	* 参数： 温度数据、湿度数据、温度结果、湿度结果
	* 无返回
  */
static void SHT10_Cal(uint16_t Temp,uint16_t Hum, float* pTempValue,float* pHumValue)
{ 
	
	const float d1 = -40.1;
	const float d2 = 0.01;
	float Temp_C;
	const float C1 = -2.0468;           
	const float C2 = +0.0367;           
	const float C3 = -0.0000015955;     
	const float T1 = +0.01;             
	const float T2 = +0.00008;           
	// 湿度线性值
	float RH_Lin;
	// 湿度真实值
	float RH_True; 
  //温度结果转换	   
	Temp_C = d1 + d2 * Temp;  
	// RH 线性结果
	RH_Lin = C1 + C2 * Hum + C3 * Hum *Hum;
	RH_True = (Temp_C - 25) * (T1 + T2 * Hum) + RH_Lin;
	// 限定范围
	if(RH_True > 100 ) RH_True = 100; 
	if(RH_True < (float) 0.01) RH_True =(float) 0.01;
	*pTempValue = Temp_C;
	*pHumValue = RH_True;	
} 
/* 
       发送完数据后等待 串口响应 
*/
uint8_t waitForUsartAdd(uint16_t adds,uint16_t times)
{
	OS_ERR err;
	uint16_t * points;
	void *Fie;
	float BufTemp,BufTemp1;
	uint8_t buff[4];
	GPIO_SetBits(GPIOA,GPIO_Pin_4);    // set   485 as outPut
	Usart2_sendChar(adds); // adds
	USART2_RX_STA=0;
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);  // reset 485 as input
	OSSemPend((OS_SEM *)&Usart2RecerveSem,
					(OS_TICK )times,
					(OS_OPT  )OS_OPT_PEND_BLOCKING,
					(CPU_TS  )NULL,
					(OS_ERR *)&err); 	
	if(err==0)   //成功返回
	{
		if((rece2_buff[0]+(0x01<<8))==adds)
		{
			if(rece2_buff[Base+1]!=0 && rece2_buff[Base]!=0 && rece2_buff[Base+2]!=0)
			{
				buff[0]=rece2_buff[Base+1];
				buff[1]=rece2_buff[Base];	
				Fie=(void*)buff;
				points = (uint16_t *)Fie;
				tempval=(*points);
				buff[0]=rece2_buff[Base+3];
				buff[1]=rece2_buff[Base+2];			
				Fie=(void*)buff;
				points = (uint16_t *)Fie;
				hempval=(*points);			
				SHT10_Cal(tempval,hempval,&Tempss,&Hempss);	
				//if(Tempss>=0 && Tempss<=100)
				/* 滤波 算法 */
				BufTemp=tempHempAndTem[rece2_buff[0]-1][0];
				BufTemp1=Tempss-BufTemp;
				BufTemp1=absFloat(BufTemp1);
				if(BufTemp1>=5)
				{
					if(getInformation[rece2_buff[0]-1].T_tmp==0 && lastTempHemp[rece2_buff[0]-1][0]==0)  // 都为0 的时候 开始计数 
					{
						getInformation[rece2_buff[0]-1].T_tmp=Tempss;
						lastTempHemp[rece2_buff[0]-1][0]=getInformation[rece2_buff[0]-1].T_tmp;
					}
					else
					{
						getInformation[rece2_buff[0]-1].T_tmp=lastTempHemp[rece2_buff[0]-1][0];
					}
				}else{					
					lastTempHemp[rece2_buff[0]-1][0]=getInformation[rece2_buff[0]-1].T_tmp;
					getInformation[rece2_buff[0]-1].T_tmp=Tempss;
				}
				tempHempAndTem[rece2_buff[0]-1][0]=Tempss;   //缓存 
			  
				//if(Hempss>=0 && Hempss<=100)
				BufTemp=tempHempAndTem[rece2_buff[0]-1][1];
				BufTemp1=Hempss-BufTemp;
				BufTemp1=absFloat(BufTemp1);
				if(BufTemp1>=5)
				{
					if(getInformation[rece2_buff[0]-1].T_hemp==0  && lastTempHemp[rece2_buff[0]-1][1]==0)  // 开始起计数
					{
						getInformation[rece2_buff[0]-1].T_hemp=Hempss;						
						lastTempHemp[rece2_buff[0]-1][1]=getInformation[rece2_buff[0]-1].T_hemp;

					}else{
						getInformation[rece2_buff[0]-1].T_hemp=lastTempHemp[rece2_buff[0]-1][1];
					}
				}else{					
					lastTempHemp[rece2_buff[0]-1][1]=getInformation[rece2_buff[0]-1].T_hemp;
					getInformation[rece2_buff[0]-1].T_hemp=Hempss;
				}
				tempHempAndTem[rece2_buff[0]-1][1]=Hempss;   //缓存 
				// getInformation[rece2_buff[0]-1].T_hemp=Hempss;				
			}
			if(rece2_buff[Base+5]!=0 && rece2_buff[Base+4]!=0 && rece2_buff[Base+6]!=0)
			{
				buff[0]=rece2_buff[Base+5];
				buff[1]=rece2_buff[Base+4];	
				Fie=(void*)buff;
				points = (uint16_t *)Fie;
				tempval=(*points);
				buff[0]=rece2_buff[Base+7];
				buff[1]=rece2_buff[Base+6];			
				Fie=(void*)buff;
				points = (uint16_t *)Fie;
				hempval=(*points);			
				SHT10_Cal(tempval,hempval,&Tempss,&Hempss);	
//								//if(Tempss>=0 && Tempss<=100)
//					getInformation[rece2_buff[0]-1].K_tmp=Tempss;
//				//if(Hempss>=0 && Hempss<=100)
//					getInformation[rece2_buff[0]-1].K_hemo=Hempss;	
					//if(Tempss>=0 && Tempss<=100)
					/* 滤波 算法 */
					BufTemp=tempHempAndTem[rece2_buff[0]-1][2];
					BufTemp1=Tempss-BufTemp;
					BufTemp1=absFloat(BufTemp1);
					if(BufTemp1>=5)
					{
						if(getInformation[rece2_buff[0]-1].K_tmp==0 && tempHempAndTem[rece2_buff[0]-1][2]==0 )
						{
							getInformation[rece2_buff[0]-1].K_tmp=Tempss;
							lastTempHemp[rece2_buff[0]-1][2]=getInformation[rece2_buff[0]-1].K_tmp;
						}else{
							getInformation[rece2_buff[0]-1].K_tmp=lastTempHemp[rece2_buff[0]-1][2];
						}
					}else{					
						lastTempHemp[rece2_buff[0]-1][2]=getInformation[rece2_buff[0]-1].K_tmp;
						getInformation[rece2_buff[0]-1].K_tmp=Tempss;
					}
					tempHempAndTem[rece2_buff[0]-1][2]=Tempss;   //缓存 
					
					//if(Hempss>=0 && Hempss<=100)
					BufTemp=tempHempAndTem[rece2_buff[0]-1][3];
					BufTemp1=Hempss-BufTemp;
					BufTemp1=absFloat(BufTemp1);
					if(BufTemp1>=5)
					{
						if(getInformation[rece2_buff[0]-1].K_hemo==0 && lastTempHemp[rece2_buff[0]-1][3]==0)
						{
							getInformation[rece2_buff[0]-1].K_hemo=Hempss;	
							lastTempHemp[rece2_buff[0]-1][3]=getInformation[rece2_buff[0]-1].K_hemo;							
						}else{
							getInformation[rece2_buff[0]-1].K_hemo=lastTempHemp[rece2_buff[0]-1][3];
						}
					}else{					
						lastTempHemp[rece2_buff[0]-1][3]=getInformation[rece2_buff[0]-1].K_hemo;
						getInformation[rece2_buff[0]-1].K_hemo=Hempss;
					}
					tempHempAndTem[rece2_buff[0]-1][3]=Hempss;   //缓存 		
				
			}
			USART2_RX_STA=0;
			return 1;
		}	
	}
	if(err==OS_ERR_TIMEOUT)
	{
			err++;
	}
	if(err==OS_ERR_OBJ_TYPE)
	{
		OSSemCreate((OS_SEM    *)&Usart2RecerveSem,
								(CPU_CHAR  *)"Usart2RecerveSem",
								(OS_SEM_CTR )0,
								(OS_ERR    *)&err);			
	}
	USART2_RX_STA=0;
	return 0;
}
void askAddress(uint8_t adds)
{
	uint8_t rece;
	uint16_t adds_tmp;
	if(adds<=8 && adds>0)
	{
		adds_tmp=(0x01<<8)+adds;
		rece=waitForUsartAdd(adds_tmp,time_out_dely);
		
		if(rece!=1 && getInformation[adds-1].flag==0)
		{
			getInformation[adds-1].K_hemo=0;
			getInformation[adds-1].K_tmp=0;
			getInformation[adds-1].T_hemp=0;
			getInformation[adds-1].T_tmp=0;
		}
		getInformation[adds-1].flag=rece;
	}
}

void AppTaskDateConnected(void *p_arg)
{
	OS_ERR     err;
//	uint8_t ubts;
	uint8_t i;
	static uint32_t tims_counters;
	int32_t AppTemp;    // 有符号 32 位数据
	GPIO_InitTypeDef GPIO_InitStructure;
	/* 创建 信号量 用与同步两个进程 */
	// 用于同步  cn=0;
	OSSemCreate((OS_SEM    *)&Usart2RecerveSem,
							(CPU_CHAR  *)"Usart2RecerveSem",
							(OS_SEM_CTR )0,
							(OS_ERR    *)&err);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
  USART2_RX_STA=0;
	tims_counters=0;
	
	while(1)
	{
		tims_counters++;
		for(i=1;i<=8;i++)
		{
			askAddress(i);
			OSTimeDlyHMSM((CPU_INT16U) 0u,
							(CPU_INT16U) 0u,
							(CPU_INT16U) 0,
							(CPU_INT32U) 30,
							(OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
							(OS_ERR   *)&err);	
		}		  
		OSTimeDlyHMSM((CPU_INT16U) 0u,
                  (CPU_INT16U) 0u,
                  (CPU_INT16U) 0,
                  (CPU_INT32U) 100,
                  (OS_OPT    ) OS_OPT_TIME_HMSM_STRICT,
                  (OS_ERR   *)&err);	
		/*  数据存储 */
		if(numbersDrawing==0)
		{
				for(i=0;i<8;i++)
				{
					if(!(getInformation[i].K_hemo==0 && getInformation[i].T_tmp==0))
					{
						DrawingDataSave[i][0][numbersDrawing]=(uint8_t) getInformation[i].K_tmp;
						DrawingDataSave[i][1][numbersDrawing]=(uint8_t) getInformation[i].K_hemo;
						DrawingDataSave[i][2][numbersDrawing]=(uint8_t) getInformation[i].T_tmp;
						DrawingDataSave[i][3][numbersDrawing]=(uint8_t) getInformation[i].T_hemp;
					}else{
						DrawingDataSave[i][0][numbersDrawing]=0;
						DrawingDataSave[i][1][numbersDrawing]=0;
						DrawingDataSave[i][2][numbersDrawing]=0;
						DrawingDataSave[i][3][numbersDrawing]=0;
					}
				}
				numbersDrawing++;
		}
		if(flag_clock==0)
		{			 
			clk1=OSTimeGet(&err);
			clkOld=clk1;
			flag_clock=1;
		}else{
			clk1=OSTimeGet(&err);
			AppTemp=clk1-clkOld;
			if(AppTemp<0)  AppTemp+=2147483647;    //2^31-1 
			if(AppTemp>=SAVEDATATIME)
			{
				for(i=0;i<8;i++)
				{
					if(!(getInformation[i].K_tmp==0 && getInformation[i].T_hemp==0))
					{
						DrawingDataSave[i][0][numbersDrawing]=(uint8_t) getInformation[i].K_tmp;
						DrawingDataSave[i][1][numbersDrawing]=(uint8_t) getInformation[i].K_hemo;
						DrawingDataSave[i][2][numbersDrawing]=(uint8_t) getInformation[i].T_tmp;
						DrawingDataSave[i][3][numbersDrawing]=(uint8_t) getInformation[i].T_hemp;
					}else{
						DrawingDataSave[i][0][numbersDrawing]=0;
						DrawingDataSave[i][1][numbersDrawing]=0;
						DrawingDataSave[i][2][numbersDrawing]=0;
						DrawingDataSave[i][3][numbersDrawing]=0;
					}
				}
				numbersDrawing++;
				if(numbersDrawing>=200)  numbersDrawing=0;
				flag_clock=0;
			}
		}
	}	  
}

