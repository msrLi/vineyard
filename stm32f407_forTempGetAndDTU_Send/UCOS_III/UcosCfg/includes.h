/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2014; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                     ST Microelectronics STM32
*                                              with the
*
*                                           STM3240G-EVAL
*                                         Evaluation Board
*
* Filename      : includes.h
* Version       : V1.00
* Programmer(s) : DC
*********************************************************************************************************
*/

#ifndef  INCLUDES_PRESENT
#define  INCLUDES_PRESENT


/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/

#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <string.h>

/*
*********************************************************************************************************
*                                              LIBRARIES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <lib_ascii.h>
#include  <lib_math.h>
#include  <lib_mem.h>
#include  <lib_str.h>
#include"Story_datas.h"

/*
*********************************************************************************************************
*                                                 OS
*********************************************************************************************************
*/

#include  <os.h>


/*
*********************************************************************************************************
*                                              APP / BSP
*********************************************************************************************************
*/
#include  <app_cfg.h>
// #include  <bsp.h>
/****************************************************************************************************
*                                          Task  
****************************************************************************************************
*/
#include"Task_dateConnected.h"
#include"Task_DtuDely.h"
/*
*********************************************************************************************************
*                                               SERIAL
*********************************************************************************************************
*/

#if (APP_CFG_SERIAL_EN == DEF_ENABLED)
#include  <app_serial.h>
#endif

#include<bsp_os.h>
#include"Task_GUI.h"
#include"BspLCDDrive.h"
#include"BspLcdHal_Init.h"
#include"LCD_interface.h"
#include"GUI_Fist_Page.h"
#include"Bsp_Timers.h"
#include"Bsp_Usart1.h"
#include"Bsp_Usart2.h"
#include"Bsp_Usart3.h"
#include"Task_dateConnected.h"
#include"exchangeData.h"
/*
*********************************************************************************************************
*                                            INCLUDES END
*********************************************************************************************************
*/

#endif

