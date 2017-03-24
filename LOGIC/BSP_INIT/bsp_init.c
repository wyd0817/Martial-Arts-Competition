/*
*********************************************************************************************************
*
*	ģ������ : BSP_INITģ��(For STM32F1XX)
*	�ļ����� : bsp_init.c
*	��    �� : V1.0
*	˵    �� : ���ǵײ����������ļ���ÿ��c�ļ����� #include "logic.h" ���������е���������ģ�顣
*			   bsp_init = Borad surport packet init �弶֧�ְ���ʼ��   
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2013-03-01  CYSY   ��ʽ����
*
*	Copyright (C), 2014-2024, ��ԭ��ӥ������
*
*********************************************************************************************************
*/

#include "bsp_init.h"
#include "logic_elimination.h"

delay_var delay_var_0,delay_var_1,delay_var_2,delay_var_3;

void Init_delay_var(delay_var *delay_var)
{
	delay_var->SoftTimerCounter = 0;
	delay_var->Allow_SoftTimer = 0;
}
void bsp_Init(void)
{
	/***********************************оƬ��ʼ��******************************************/
	
	NVIC_Configuration();		//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();						//��ʱ������ʼ��	  
	uart_init(9600);				//���ڳ�ʼ��Ϊ9600
	LED_Init();							//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();			 			  //��ʼ������
	BEEP_Init();						//��ʼ��������
	Edge_Io_Init();
	Adc_Init(); 		 			  //��ʼ��ADCģ��
	Enemy_Init();					 //��ʼ�������˵İ˸�����
	OLED_IO_Init();					//OLED��I/O���ų�ʼ��
	OLED_Init(0);						//��ʼ��OLED 
	OLED_Init(1);						//��ʼ��OLED 
	TIM6_Configuration();		//��ʼ����ʱ��6
	TIM7_Configuration();		//��ʼ����ʱ��7
	TIM5_PWM_Init(1000-1,3-1);//����Ƶ��PWMƵ��=72000000/(3*1000)=24Khz������Ƽ�Ƶ�ʣ�
	
	Init_delay_var(&delay_var_0);
	Init_delay_var(&delay_var_1);
	Init_delay_var(&delay_var_2);
	Init_delay_var(&delay_var_3);
	
	/******************  (������)~ ********* (��?��) ********* <(�����)>   ******************/
}	


/***************************** ��ԭ��ӥ������ CYSY (END OF FILE) *********************************/

