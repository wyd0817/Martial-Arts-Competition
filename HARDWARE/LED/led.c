#include "led.h"

//初始化PA1，PA2为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //使能PA端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //LED0-->PA.1 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.1
 GPIO_SetBits(GPIOE,GPIO_Pin_1);						 //PA.1 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PA.2 端口配置, 推挽输出
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOE,GPIO_Pin_2); 						 //PA.2 输出高 
} 
