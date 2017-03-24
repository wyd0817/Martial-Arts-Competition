/*
*********************************************************************************************************
*
*	模块名称 : BSP_INIT模块(For STM32F1XX)
*	文件名称 : bsp_init.c
*	版    本 : V1.0
*	说    明 : 这是底层驱动的主文件。每个c文件可以 #include "logic.h" 来包含所有的外设驱动模块。
*			   bsp_init = Borad surport packet init 板级支持包初始化   
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2013-03-01  CYSY   正式发布
*
*	Copyright (C), 2014-2024, 草原神鹰工作组
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
	/***********************************芯片初始化******************************************/
	
	NVIC_Configuration();		//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	delay_init();						//延时函数初始化	  
	uart_init(9600);				//串口初始化为9600
	LED_Init();							//初始化与LED连接的硬件接口
	KEY_Init();			 			  //初始化按键
	BEEP_Init();						//初始化蜂鸣器
	Edge_Io_Init();
	Adc_Init(); 		 			  //初始化ADC模块
	Enemy_Init();					 //初始化检测敌人的八个引脚
	OLED_IO_Init();					//OLED的I/O引脚初始化
	OLED_Init(0);						//初始化OLED 
	OLED_Init(1);						//初始化OLED 
	TIM6_Configuration();		//初始化定时器6
	TIM7_Configuration();		//初始化定时器7
	TIM5_PWM_Init(1000-1,3-1);//不分频。PWM频率=72000000/(3*1000)=24Khz（店家推荐频率）
	
	Init_delay_var(&delay_var_0);
	Init_delay_var(&delay_var_1);
	Init_delay_var(&delay_var_2);
	Init_delay_var(&delay_var_3);
	
	/******************  (￣▽￣)~ ********* (⊙?⊙) ********* <(￣︶￣)>   ******************/
}	


/***************************** 草原神鹰工作组 CYSY (END OF FILE) *********************************/

