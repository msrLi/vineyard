#include"SHT10_01.h"


#define noACK 0 // 无应答
#define ACK   1 // 应答

#define STATUS_REG_W    0x06   //000   0011    0
#define STATUS_REG_R    0x07   //000   0011    1
#define MEASURE_TEMP    0x03   //000   0001    1
#define MEASURE_HUMI    0x05   //000   0010    1
#define RESET           0x1e   //000   1111    0
uint32_t adfd;
/* Private variables ---------------------------------------------------------*/

uint8_t Test_Timetick_1 = 0;
uint16_t Test_Counter_1 = 0;
/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  初始化 SHT10 IO 口
  * @param  None
  * @retval None
  */
void SHT10_Config_1(void)
{
    GPIO_Init(SCK_BAS_1,SCK_Pin_1,GPIO_MODE_OUT_OD_HIZ_SLOW);   //SCK  初始化 输出 
    GPIO_Init(SDA_BAS_1,SDA_Pin_1,GPIO_MODE_OUT_OD_HIZ_SLOW);    
    SDA_H_1();
    SCK_L_1();
}
/**
  * @brief  配置SDA引脚为输入 
  * @param  None
  * @retval None
  */
void SHT10_SDAIn_1(void)
{
    GPIO_Init(SDA_BAS_1,SDA_Pin_1,GPIO_MODE_IN_FL_NO_IT); 
 
}
/**
  * @brief  配置为输出状态
  * @param  None
  * @retval None
  */
void SHT10_SDAOut_1(void)
{
     GPIO_Init(SDA_BAS_1,SDA_Pin_1,GPIO_MODE_OUT_OD_HIZ_SLOW);
     SDA_H_1();
}
/**
  * @brief  写数据
  * @param  将写入的数据
  * @retval 应答
  */
uint8_t SHT10_WriteByte_1(uint8_t value)
{ 
    uint8_t i,error=0;  
    //SDA??
    SHT10_SDAOut_1();
    
    for( i = 0x80 ; i>0 ; i/=2)             
    { 
        if ( i & value) 
            SDA_H_1();            
        else 
            SDA_L_1();
        
        SHT10_Delay_1();                       
        SCK_H_1();                          
        SHT10_Delay_1();                       
        SCK_L_1();
        SHT10_Delay_1();                     
    }
    
    //SDA输入
    SHT10_SDAIn_1();
    
    SCK_H_1();    
    
    error = SDA_R_1();   // 读取应答位             
    SCK_L_1(); 
    
    return error;                 
}
/**
  * @brief  读数据
  * @param  应答
  * @retval 返回数据
  */
uint8_t SHT10_ReadByte_1(uint8_t Ack)
{ 
    uint8_t i,val=0;
    uint8_t reads=0;
    //输入状态
    SHT10_SDAIn_1();  
    
    for (i=0x80;i>0;i/=2)         
    { 
        SHT10_Delay_1();  
        SCK_H_1();   
        SHT10_Delay_1(); 
        reads=SDA_R_1();
        if(reads) 
            val=(val | i);        //读数据
        SCK_L_1();                                           
    }
    
    //输出状态
    SHT10_SDAOut_1();  
    if(Ack)
        SDA_L_1();                //应答为低电平
    else
        SDA_H_1();

    SHT10_Delay_1();  
    SCK_H_1();                     
    SHT10_Delay_1();  
    SCK_L_1();
    SHT10_Delay_1();                                              
    return val;
}
/**
  * @brief  启动
  * @param  无
  * @retval 无
  */
void SHT10_Start_1(void)
{  
   //SDA??
    SHT10_SDAOut_1();
   
    SCK_L_1();                   
    SHT10_Delay_1();          
    SCK_H_1();
    SHT10_Delay_1(); 
    SHT10_Delay_1();
    SDA_L_1();
    SHT10_Delay_1();          
    SCK_L_1();  
    SHT10_Delay_1();          
    SCK_H_1();
    SHT10_Delay_1(); 
    SHT10_Delay_1(); 
    SDA_H_1();                   
    SHT10_Delay_1();          
    SCK_L_1();    
}
/**
  * @brief  重新连接
  * @param  无
  * @retval 无
  */
void SHT10_ConReset_1(void)
{
    uint8_t i;
    //输出状态
    SHT10_SDAOut_1();
    
    SDA_H_1();    //输出高电平
    SCK_L_1();
   //  SHT10_Delay_1();
    for(i = 0 ; i < 9 ; i++)                  
    { 
        SCK_H_1();
        SHT10_Delay_1();
        SCK_L_1();
        SHT10_Delay_1();
    }
    
    SHT10_Start_1();                   
}
/**
  * @brief  软件重启
  * @param  无
  * @retval 无
  */
uint8_t SHT10_SoftReset_1(void)
{ 
    uint8_t error=0;  
    SHT10_ConReset_1();              
    error += SHT10_WriteByte_1(RESET);       
    return error;                    
}
/**
  * @brief  温度或湿度测量
  * @param  温度或者湿度指针数据，校验值指针，模式
  * @retval 错误
  */
uint8_t SHT10_Measure_1(uint16_t* pValue, uint8_t* pCheckSum, uint8_t mode)
{ 
    uint8_t error=0;
    uint8_t Value_H = 0;
    uint8_t Value_L = 0;
    uint8_t readsl;
    //启动
    SHT10_Start_1();                
    switch(mode)
    {                     
    case TEMP1: 
        error += SHT10_WriteByte_1(MEASURE_TEMP); 
        break;
    case HUMI1: 
        error += SHT10_WriteByte_1(MEASURE_HUMI); 
        break;
    default: 
        break;         
    }
    
    //SDA输入状态
    SHT10_SDAIn_1();
    //等待转换完成 容易死循环  
    readsl=SDA_R_1();
    adfd=4000;
    while(readsl && adfd>0 )  // && i
    {
        readsl=SDA_R_1();
        if(adfd>0)
          adfd--;
        
    }
    if(adfd<=0) return 0;

    Value_H = SHT10_ReadByte_1(ACK);    //读高位
    Value_L = SHT10_ReadByte_1(ACK);    //读低位
   
    *pCheckSum = SHT10_ReadByte_1(noACK);  //读校验结果
    
    //返回结果
    *pValue = (Value_H << 8) | Value_L;    
    
    return error;
}
/**
  * @brief  计算温度和湿度数据
  * @param  温度数据，湿度数据，温度结果，湿度结果
  * @retval 无
  */
void SHT10_Cal_1(uint16_t Temp,uint16_t Hum, float* pTempValue,float* pHumValue)
{ 
    const float d1 = -40.1;
    const float d2 = 0.01;
    float Temp_C;
    const float C1 = -2.0468;           
    const float C2 = +0.0367;           
    const float C3 = -0.0000015955;     
    const float T1 = +0.01;             
    const float T2 = +0.00008;           
    //湿度线性值
    float RH_Lin;
    //湿度真实值
    float RH_True; 
	
	 //温度结果 ，换算       
    Temp_C = d1 + d2 * Temp;  
    //RH线性结果
    RH_Lin = C1 + C2 * Hum + C3 * Hum *Hum;
    RH_True = (Temp_C - 25) * (T1 + T2 * Hum) + RH_Lin;
    //限定范围
    if( RH_True > 100 ) RH_True = 100; 
    if( RH_True < 0.01) RH_True = 0.01;
    
    *pTempValue = Temp_C;
    *pHumValue = RH_True;
    
}
/**
  * @brief  延时函数
  * @param  无
  * @retval 无
  */
void SHT10_Delay_1(void)
{
    //延时函数,i有待修改
	 uint16_t i=0;
    for( i = 20 ; i > 0 ; i--)
    {
        ;
    }
}





