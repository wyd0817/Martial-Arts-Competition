/*
*********************************************************************************************************
*
*	模块名称 : LOGIC_ELIMINATION模块
*	文件名称 : logic_elimination.h
*
*	说    明 : 淘汰赛头文件
*
*	Copyright (C), 2014-2024, 草原神鹰工作组
*
*********************************************************************************************************
*/
#ifndef __LOGIC_ELIMINATION_H
#define __LOGIC_ELIMINATION_H
#include "sys.h"


/* 通过取消注释或者添加注释的方式控制是否包含底层驱动模块 */
#include "logic_elimination.h"
//extern delay_var delay_var_0,delay_var_1,delay_var_2,delay_var_3;

//要写入到STM32 FLASH的字符串数组

#define SIZE sizeof(TEXT_Buffer)	 			  	//数组长度
#define FLASH_SAVE_ADDR  0X08030000 				//设置FLASH 保存地址(必须为偶数)

#define RIGH_FRONT_1	(Flag_Enemy&0x01)//右前1
#define RIGH_FRONT_2	(Flag_Enemy&0x02)//右前2
#define LEFT_FRONT_2	(Flag_Enemy&0x04)//左前2
#define LEFT_FRONT_1	(Flag_Enemy&0x08)//左前1
#define LEFT_AFTER_1	(Flag_Enemy&0x10)//左后1
#define LEFT_AFTER_2	(Flag_Enemy&0x20)//左后2	
#define RIGH_AFTER_2	(Flag_Enemy&0x40)//右后2
#define RIGH_AFTER_1	(Flag_Enemy&0x80)//右后1

#define LEFT_AFTER_T	(Flag_Margin&0x01)//左后Table
#define RIGH_AFTER_T	(Flag_Margin&0x02)//右后Table
#define LEFT_FRONT_T	(Flag_Margin&0x04)//左前Table
#define RIGH_FRONT_T	(Flag_Margin&0x08)//右前Table
	
#define LEFT_ENEMY_Y	(Flag_Size&0x01) //左面Yellow
#define RIGH_ENEMY_Y	(Flag_Size&0x02) //右面Yellow


/* 提供给其他C文件调用的函数 */
void Init_Elimination(void);
void Chess_1_Margin_0(void);
void Chess_0_Margin_1(void);
void Chess_0_Margin_0(void);
void Chess_1_Margin_1(void);

#endif

/***************************** 草原神鹰工作组 CYSY (END OF FILE) *********************************/


