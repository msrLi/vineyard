#include"Key_Drive.h"
const char Key_value[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
static void dealy(u16 num)
{  
    Timer1=num;
    while(Timer1);
}
static uint8_t analysize(uint8_t row)
{  
    uint8_t key_find;
    uint8_t key_re='$';
    uint8_t i;
    for(i=0;i<4;i++)
    {
       key_find = (uint8_t)(Key_lie>>i)&0x00000001;
       if(!key_find)
       {
         key_re = Key_value[row][i];
         break;
       }
    }
    return key_re;
}
static void set_out()
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
/**********************set out put ************************/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//    
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//    // 输出零行 
//    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
//    GPIO_ResetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7);
//    // GPIO_ResetBits(GPIOC, GPIO_Pin_11);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
    GPIO_Init(GPIOE, &GPIO_InitStructure);    

	GPIO_ResetBits(GPIOC, GPIO_Pin_5);
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	GPIO_ResetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 );
}
static void read_all()
{
    GPIO_InitTypeDef GPIO_InitStructure;
   /******************set input *****************************/    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   //up down input 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//    GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//    GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
//    GPIO_Init(GPIOE, &GPIO_InitStructure);

//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8;
//    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

     // 读取 列值的大小 
    (*(volatile u32 *) Key_red5) = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);
    (*(volatile u32 *) Key_red6) = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);
    (*(volatile u32 *) Key_red7) = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5);
    (*(volatile u32 *) Key_red8) = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7); 
}
static uint8_t set_scan(uint8_t num)
{
    uint8_t key;
    GPIO_InitTypeDef GPIO_InitStructure;
/**********************set out put ************************/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//    
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7;
//    GPIO_Init(GPIOA, &GPIO_InitStructure); 
//    GPIO_SetBits(GPIOA, GPIO_Pin_1);
//    GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
    GPIO_Init(GPIOE, &GPIO_InitStructure);    

	GPIO_SetBits(GPIOC, GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 );

    switch(num)
    {
    case 0: GPIO_ResetBits(GPIOC,GPIO_Pin_5);key=0;break;
    case 1: GPIO_ResetBits(GPIOB,GPIO_Pin_1);key=1;break;
    case 2: GPIO_ResetBits(GPIOE,GPIO_Pin_7);key=2;break;
    case 3: GPIO_ResetBits(GPIOE,GPIO_Pin_8);key=3;break;
    default : key=0xff;break;
    }
    return key;
}
uint8_t Key_scan()
{
    uint32_t key_num;
    uint8_t i;
    uint8_t key_re='$';
    set_out();
    read_all();
    key_num = (uint32_t)((~Key_lie)&0x0000000F);
    if(key_num)
    {  
      dealy(10); 
      read_all();
       key_num = (uint32_t)((~Key_lie)&0x0000000F);
       if(key_num)
       {
           for(i=0;i<4;i++)
           {
               set_scan(i);
               read_all();
               key_num = (uint32_t)((~Key_lie)&0x0000000F);
               if(key_num)
               {
                  dealy(10);
                  set_scan(i);
                  read_all();
                  key_re=analysize(i);
                  break;
               }
           }
       }
    }
    return key_re;
}
