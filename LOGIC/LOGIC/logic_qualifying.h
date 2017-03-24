/*
*********************************************************************************************************
*
*	模块名称 : LOGIC_QUALIFYING块
*	文件名称 : logic_qualifying.h
*
*	说    明 : 排位赛头文件
*
*	Copyright (C), 2014-2024, 草原神鹰工作组
*
*********************************************************************************************************
*/
#ifndef __LOGIC_QUALIFYING_H
#define __LOGIC_QUALIFYING_H
#include "sys.h"

/* 通过取消注释或者添加注释的方式控制是否包含底层驱动模块 */
#include "logic_qualifying.h"

/* 通过取消注释或者添加注释的方式控制是否包含底层驱动模块 */
#include "logic_elimination.h"

/* 提供给其他C文件调用的函数 */
void Init_Qualifying(void);

void Enemy_1_Margin_0(void);
void Enemy_0_Margin_1(void);
void Enemy_0_Margin_0(void);
void Enemy_1_Margin_1(void);

#endif

/***************************** 草原神鹰工作组 CYSY (END OF FILE) *********************************/


