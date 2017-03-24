/*
*********************************************************************************************************
*
*	模块名称 : BSP_INIT模块
*	文件名称 : bsp_init.h
*	说    明 : 这是底层驱动模块所有的h文件的汇总文件。 应用程序只需 #include bsp.h 即可，
*			  不需要#include 每个模块的 h 文件
*
*	Copyright (C), 2014-2024, 草原神鹰工作组
*
*********************************************************************************************************
*/
#ifndef __BSP_INIT_H
#define __BSP_INIT_H
#include "sys.h"


/* 通过取消注释或者添加注释的方式控制是否包含底层驱动模块 */
#include "led.h"
#include "key.h"
#include "beep.h"
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "usart.h"
#include "exti.h"
#include "adc.h"
#include "timer.h"
#include "timer_7.h" 
#include "car.h"
#include "config.h"
#include "stmflash.h"
#include "multilevel.h"

typedef struct delay_var
{
	u32 SoftTimerCounter;//计数变量
	u8 Allow_SoftTimer;//允许定时器计数
} delay_var;

/* 提供给其他C文件调用的函数 */
void bsp_Init(void);

#endif

/***************************** 草原神鹰工作组 CYSY (END OF FILE) *********************************/



