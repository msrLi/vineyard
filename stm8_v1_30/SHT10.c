#include"SHT10.h"

int32_t datas=0;
#define noACK 0 // 无应答
#define ACK   1 // 应答

#define STATUS_REG_W    0x06   //000   0011    0
#define STATUS_REG_R    0x07   //000   0011    1
#define MEASURE_TEMP    0x03   //000   0001    1
#define MEASURE_HUMI    0x05   //000   0010    1
#define RESET           0x1e   //000   1111    0

/* Private variables ---------------------------------------------------------*/

uint8_t Test_Timetick = 0;
uint16_t Test_Counter = 0;
/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  初始化 SHT10 IO 口
  * @param  None
  * @retval None
  */
void SHT10_Config(void)
{
    GPIO_Init(SCK_BAS ,SCK_Pin ,GPIO_MODE_OUT_OD_HIZ_SLOW);   //SCK  初始化 输出 
    GPIO_Init(SDA_BAS ,SDA_Pin ,GPIO_MODE_OUT_OD_HIZ_SLOW);    
    SDA_H();
    SCK_L();
}
/**
  * @brief  配置SDA引脚为输入 
  * @param  None
  * @retval None
  */
void SHT10_SDAIn (void)
{
    GPIO_Init(SDA_BAS,SDA_Pin,GPIO_MODE_IN_FL_NO_IT); 
 
}
/**
  * @brief  配置为输出状态
  * @param  None
  * @retval None
  */
void SHT10_SDAOut (void)
{
     GPIO_Init(SDA_BAS ,SDA_Pin ,GPIO_MODE_OUT_OD_HIZ_SLOW);
     SDA_H ();
}
/**
  * @brief  写数据
  * @param  将写入的数据
  * @retval 应答
  */
uint8_t SHT10_WriteByte (uint8_t value)
{ 
    uint8_t i,error=0;  
    //SDA??
    SHT10_SDAOut ();
    
    for( i = 0x80 ; i>0 ; i/=2)             
    { 
        if ( i & value) 
            SDA_H ();            
        else 
            SDA_L ();
        
        SHT10_Delay ();                       
        SCK_H ();                          
        SHT10_Delay ();                       
        SCK_L ();
        SHT10_Delay ();                     
    }
    
    //SDA输入
    SHT10_SDAIn ();
    
    SCK_H ();    
    
    error = SDA_R ();   // 读取应答位             
    SCK_L (); 
    
    return error;                 
}
/**
  * @brief  读数据
  * @param  应答
  * @retval 返回数据
  */
uint8_t SHT10_ReadByte (uint8_t Ack)
{ 
    uint8_t i,val=0;
    uint8_t reads=0;
    //输入状态
    SHT10_SDAIn ();  
    
    for (i=0x80;i>0;i/=2)         
    { 
        SHT10_Delay ();  
        SCK_H ();   
        SHT10_Delay (); 
        reads=SDA_R ();
        if(reads) 
            val=(val | i);        //读数据
        SCK_L ();                                           
    }
    
    //输出状态
    SHT10_SDAOut ();  
    if(Ack)
        SDA_L ();                //应答为低电平
    else
        SDA_H ();

    SHT10_Delay ();  
    SCK_H ();                     
    SHT10_Delay ();  
    SCK_L ();
    SHT10_Delay ();                                              
    return val;
}
/**
  * @brief  启动
  * @param  无
  * @retval 无
  */
void SHT10_Start (void)
{  
   //SDA??
    SHT10_SDAOut ();
   
    SCK_L ();                   
    SHT10_Delay ();          
    SCK_H ();
    SHT10_Delay (); 
    SHT10_Delay ();
    SDA_L ();
    SHT10_Delay ();          
    SCK_L ();  
    SHT10_Delay ();          
    SCK_H ();
    SHT10_Delay (); 
    SHT10_Delay (); 
    SDA_H ();                   
    SHT10_Delay ();          
    SCK_L ();    
}
/**
  * @brief  重新连接
  * @param  无
  * @retval 无
  */
void SHT10_ConReset (void)
{
    uint8_t i;
    //输出状态
    SHT10_SDAOut ();
    
    SDA_H ();    //输出高电平
    SCK_L ();
   //  SHT10_Delay ();
    for(i = 0 ; i < 9 ; i++)                  
    { 
        SCK_H ();
        SHT10_Delay ();
        SCK_L ();
        SHT10_Delay ();
    }
    
    SHT10_Start ();                   
}
/**
  * @brief  软件重启
  * @param  无
  * @retval 无
  */
uint8_t SHT10_SoftReset (void)
{ 
    uint8_t error=0;  
    SHT10_ConReset ();              
    error += SHT10_WriteByte (RESET);       
    return error;                    
}
/**
  * @brief  温度或湿度测量
  * @param  温度或者湿度指针数据，校验值指针，模式
  * @retval 错误
  */
uint8_t SHT10_Measure (uint16_t* pValue, uint8_t* pCheckSum, uint8_t mode)
{ 
    uint8_t error=0;
    uint8_t Value_H = 0;
    uint8_t Value_L = 0;
    uint8_t readsl;
    //启动
    SHT10_Start ();                
    switch(mode)
    {                     
    case TEMP: 
        error += SHT10_WriteByte (MEASURE_TEMP); 
        break;
    case HUMI: 
        error += SHT10_WriteByte (MEASURE_HUMI); 
        break;
    default: 
        break;         
    }
    
    //SDA输入状态
    SHT10_SDAIn ();
    //等待转换完成 容易死循环  
    
    // datas=0;
    readsl=SDA_R ();
    datas=4000;
    while(readsl && datas>0 )  // 
    {
        readsl=SDA_R ();
         if(datas>0)
          datas--;
         // datas++;
    }
    if(datas<=0) return 0;


    Value_H = SHT10_ReadByte (ACK);    //读高位
    Value_L = SHT10_ReadByte (ACK);    //读低位
   
    *pCheckSum = SHT10_ReadByte (noACK);  //读校验结果
    
    //返回结果
    *pValue = (Value_H << 8) | Value_L;    
    
    return error;
}
/**
  * @brief  计算温度和湿度数据
  * @param  温度数据，湿度数据，温度结果，湿度结果
  * @retval 无
  */
void SHT10_Cal (uint16_t Temp,uint16_t Hum, float* pTempValue,float* pHumValue)
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
void SHT10_Delay (void)
{
    //延时函数,i有待修改
	 uint16_t i=0;
    for( i = 20 ; i > 0 ; i--)
    {
        ;
    }
}
