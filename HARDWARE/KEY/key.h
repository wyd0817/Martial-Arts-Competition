#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

// 
//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define KEY3 PAin(0)	//PA0  WK_UP
 
#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)//��ȡ����1
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//��ȡ����2
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//��ȡ����3 
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//��ȡ����4


#define _SWTICH  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//ģʽ����

#define KEY_UP 		1
#define KEY_LEFT	2
#define KEY_DOWN	3
#define KEY_RIGHT	4

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
