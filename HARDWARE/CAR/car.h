#ifndef __CAR_H
#define __CAR_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/4
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//********************************************************************************


void TIM5_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void Car_Forward(u16 speed);
void Car_Back(u16 speed);
void Car_Pause(void);
void Car_Left_Forward(u16 speed);
void Car_Right_Forward(u16 speed);
void Car_Left_Back(u16 speed);
void Car_Right_Back(u16 speed);

void Car_Left_Forward_Chess(u16 speed);
void Car_Right_Forward_Chess(u16 speed);
void Car_Left_Back_Chess(u16 speed);
void Car_Right_Back_Chess(u16 speed);

void Car_Rotation(void);
void Car_Rotation_1(void);//�����Ӵ�ת����
void Car_Rotation_2(void);//�����Ӵ�ת����
#endif
