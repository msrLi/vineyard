#ifndef _KEY_DRIVE_H_
#define _KEY_DRIVE_H_
#include"LCD_Drive.h"
#include "stm32f10x.h"

#define Key_red1 ((u32) 0x22000000)
#define Key_red2 ((u32) 0x22000004)
#define Key_red3 ((u32) 0x22000008)
#define Key_red4 ((u32) 0x2200000C)

#define Key_red5 ((u32) 0x22000080)
#define Key_red6 ((u32) 0x22000084)
#define Key_red7 ((u32) 0x22000088)
#define Key_red8 ((u32) 0x2200008C)

#define Key_hang (*(volatile u32 *)((u32) 0x20000000))
#define Key_lie  (*(volatile u32 *)((u32) 0x20000004))

uint8_t Key_scan(void);
//static 
#endif
