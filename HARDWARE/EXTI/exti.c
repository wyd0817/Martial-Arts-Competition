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
		Edge_Io_Init();//检测边缘传感器IO引脚初始化
    

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

    
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);//PB4

  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器  

		GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);//PD2
	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能PD2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
    
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能PB4所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 	
}


void EXTI2_IRQHandler(void)//2号中断
{
 if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
 {
	 #ifdef SER_DANGER 
			printf("14号传感器检测到敌人\r\n\r\n");	
	 #endif
 }
    
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE2上的中断标志位  
}


void EXTI4_IRQHandler(void)//4号中断
{
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
 {
	 #ifdef SER_DANGER 
			printf("13号传感器检测到敌人\r\n\r\n");	
	 #endif
 }
 
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位  
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

















