/*
*********************************************************************************************************
*
*	ģ������ : ������ģ�顣
*	�ļ����� : main.c
*	��    �� : V1.0
*	˵    �� : 
*             
*             
*	�޸ļ�¼ :
*		�汾��    ����       ����            ˵��
*		v1.0    2015-03-05  ������     �˳����ǻ�����ʡ��������̨����������
*
*	Copyright (C), 2014-2024, ��ԭ��ӥ������
*
*********************************************************************************************************
*/
#include "bsp_init.h"
#include "logic_qualifying.h"
#include "logic_elimination.h"

#define _SWTICH  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//ģʽ����

extern u8 Flag_Margin;//�����̨̨���4��������(9-12)
extern u8 Flag_Enemy; //ǰ������˵�8��������(1-8)
extern u8 Flag_Size;  //��������˵�2��������(13-14)
extern delay_var delay_var_0,delay_var_1,delay_var_2,delay_var_3;
int main(void)
{

	bsp_Init();
//	while(1)
//	printf("���1 ���2 �Һ�2�е���");
		
//		while(1)
//		{
//		delay_var_0.Allow_SoftTimer=1;
//	if(delay_var_0.SoftTimerCounter<10)	Car_Left_Forward(ROUND_LOW_SPEED);
//	else									Car_Pause();
//		}
	switch(_SWTICH)
	{
		case 0:Init_Qualifying(); break;//��λ����ʼ����������̨��
		case 1:Init_Elimination();break;//��̭����ʼ����������̨��
	}
	
	while(1)
	{
		if(_SWTICH==0)
		while(1)//��λ������
		{
			if((Flag_Enemy||Flag_Size)==0)//û������
			{
				if(Flag_Margin==0)			Chess_0_Margin_0();//û�м�⵽��Ե
				else if(Flag_Margin!=0)		Chess_0_Margin_1();//��⵽��Ե
			}
			else if((Flag_Enemy!=0)||(Flag_Size!=0))//��������
			{
				if(Flag_Margin==0)			Chess_1_Margin_0();//û�м�⵽��Ե��ײ���壩	
				else if(Flag_Margin!=0)		Chess_1_Margin_1();//��⵽��Ե�������������2װ���壩	
			}	
		}
		else if(_SWTICH==1)
		while(1)//��̭������
		{
			if((Flag_Enemy||Flag_Size)==0)//û�е���
			{
				if(Flag_Margin==0)			Enemy_0_Margin_0();//û�м�⵽��Ե
				else if(Flag_Margin!=0)		Enemy_0_Margin_1();//��⵽��Ե
			}
			else if((Flag_Enemy!=0)||(Flag_Size!=0))//��������
			{
				if(Flag_Margin==0)			Enemy_1_Margin_0();//û�м�⵽��Ե��������������Ǽ�⵽���ˣ�����ģʽ��	
				else if(Flag_Margin!=0)		Enemy_1_Margin_1();//������������Ǳ�ײ�ˣ����ģʽ
			}
		}
	}
}


/*
*********************************************************************************************************
															*���Ե������*
//	Car_Forward(HIGH_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	Car_Forward(LOW_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	Car_Back(HIGH_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	Car_Back(LOW_SPEED);
//	delay_ms(1000);delay_ms(1000);
	
//	Car_Left_Forward(HIGH_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	Car_Right_Forward(HIGH_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	Car_Left_Back(HIGH_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	Car_Right_Back(HIGH_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	
//	Car_Left_Forward_Chess(LOW_SPEED);
//	Car_Right_Forward_Chess(LOW_SPEED);
//	Car_Left_Back_Chess(LOW_SPEED);
//	Car_Right_Back_Chess(LOW_SPEED);

//	Car_Pause();
//	delay_ms(1000);delay_ms(1000);
//	while(1);

*********************************************************************************************************
*/




