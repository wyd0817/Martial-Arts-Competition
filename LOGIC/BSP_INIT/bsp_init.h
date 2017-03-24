/*
*********************************************************************************************************
*
*	ģ������ : BSP_INITģ��
*	�ļ����� : bsp_init.h
*	˵    �� : ���ǵײ�����ģ�����е�h�ļ��Ļ����ļ��� Ӧ�ó���ֻ�� #include bsp.h ���ɣ�
*			  ����Ҫ#include ÿ��ģ��� h �ļ�
*
*	Copyright (C), 2014-2024, ��ԭ��ӥ������
*
*********************************************************************************************************
*/
#ifndef __BSP_INIT_H
#define __BSP_INIT_H
#include "sys.h"


/* ͨ��ȡ��ע�ͻ������ע�͵ķ�ʽ�����Ƿ�����ײ�����ģ�� */
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
	u32 SoftTimerCounter;//��������
	u8 Allow_SoftTimer;//����ʱ������
} delay_var;

/* �ṩ������C�ļ����õĺ��� */
void bsp_Init(void);

#endif

/***************************** ��ԭ��ӥ������ CYSY (END OF FILE) *********************************/



