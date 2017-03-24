/*
*********************************************************************************************************
*
*	ģ������ : LOGIC_ELIMINATIONģ��
*	�ļ����� : logic_elimination.h
*
*	˵    �� : ��̭��ͷ�ļ�
*
*	Copyright (C), 2014-2024, ��ԭ��ӥ������
*
*********************************************************************************************************
*/
#ifndef __LOGIC_ELIMINATION_H
#define __LOGIC_ELIMINATION_H
#include "sys.h"


/* ͨ��ȡ��ע�ͻ������ע�͵ķ�ʽ�����Ƿ�����ײ�����ģ�� */
#include "logic_elimination.h"
//extern delay_var delay_var_0,delay_var_1,delay_var_2,delay_var_3;

//Ҫд�뵽STM32 FLASH���ַ�������

#define SIZE sizeof(TEXT_Buffer)	 			  	//���鳤��
#define FLASH_SAVE_ADDR  0X08030000 				//����FLASH �����ַ(����Ϊż��)

#define RIGH_FRONT_1	(Flag_Enemy&0x01)//��ǰ1
#define RIGH_FRONT_2	(Flag_Enemy&0x02)//��ǰ2
#define LEFT_FRONT_2	(Flag_Enemy&0x04)//��ǰ2
#define LEFT_FRONT_1	(Flag_Enemy&0x08)//��ǰ1
#define LEFT_AFTER_1	(Flag_Enemy&0x10)//���1
#define LEFT_AFTER_2	(Flag_Enemy&0x20)//���2	
#define RIGH_AFTER_2	(Flag_Enemy&0x40)//�Һ�2
#define RIGH_AFTER_1	(Flag_Enemy&0x80)//�Һ�1

#define LEFT_AFTER_T	(Flag_Margin&0x01)//���Table
#define RIGH_AFTER_T	(Flag_Margin&0x02)//�Һ�Table
#define LEFT_FRONT_T	(Flag_Margin&0x04)//��ǰTable
#define RIGH_FRONT_T	(Flag_Margin&0x08)//��ǰTable
	
#define LEFT_ENEMY_Y	(Flag_Size&0x01) //����Yellow
#define RIGH_ENEMY_Y	(Flag_Size&0x02) //����Yellow


/* �ṩ������C�ļ����õĺ��� */
void Init_Elimination(void);
void Chess_1_Margin_0(void);
void Chess_0_Margin_1(void);
void Chess_0_Margin_0(void);
void Chess_1_Margin_1(void);

#endif

/***************************** ��ԭ��ӥ������ CYSY (END OF FILE) *********************************/


