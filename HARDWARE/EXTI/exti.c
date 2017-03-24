#include "exti.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "beep.h"
#include "car.h"
#include "config.h"



void EXTIX_Init(void)
{
 
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		Edge_Io_Init();//����Ե������IO���ų�ʼ��
    

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

    
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);//PB4

  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���  

		GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);//PD2
	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ��PD2���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ��PB4���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 	
}


void EXTI2_IRQHandler(void)//2���ж�
{
 if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
 {
	 #ifdef SER_DANGER 
			printf("14�Ŵ�������⵽����\r\n\r\n");	
	 #endif
 }
    
	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE2�ϵ��жϱ�־λ  
}


void EXTI4_IRQHandler(void)//4���ж�
{
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
 {
	 #ifdef SER_DANGER 
			printf("13�Ŵ�������⵽����\r\n\r\n");	
	 #endif
 }
 
	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ  
}


void Edge_Io_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
	
}

















