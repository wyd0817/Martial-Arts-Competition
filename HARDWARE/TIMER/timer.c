#include "timer.h" 
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "config.h"
#include "bsp_init.h"

//#define MARGIN_CRITICAL Margin_Critcal  //检测边缘传感器在台上的最小值和在台下的最大值的和一半（  出台时值则会减小）
//#define ENEMY_CRITICAL  Enemy_Critical  //检测敌人传感器危险时的最小值和安全时的最大值的和一半（有危险时值则会增大）

//#define FRONT_MARGIN_CRITICAL 2000  //（越大越灵敏  出台时值则会减小）
//#define BACK_MARGIN_CRITICAL 2000  // （越大越灵敏  出台时值则会减小）

#define FRONT_MARGIN_CRITICAL 1700  //（越大越灵敏  出台时值则会减小）
#define BACK_MARGIN_CRITICAL 1700  // （越大越灵敏  出台时值则会减小）


//#define ENEMY_CRITICAL  600  //检测敌人传感器危险时的最小值和安全时的最大值的和一半（有危险时值则会增大）

u32 Enemy_Count[10]={0};
u32 Table_Count[4]={0};
u8 Flag_Margin=0x00;
u8 Flag_Size=0x00; 

u16 Margin_Critcal=1000;
//u16 Margin_Critcal=(3300+1500)/2;


extern __IO uint16_t ADCvalue[4];
extern delay_var delay_var_0,delay_var_1,delay_var_2,delay_var_3;

//*****基本定时器6初始化*********
void TIM6_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	
	
	TIM_TimeBaseStructure.TIM_Prescaler = 200 - 1;//预分频系数为36000-1，这样计数器时钟为72MHz/36000 = 2kHz
	TIM_TimeBaseStructure.TIM_Period = 7200 - 1;//设置计数溢出大小，每计2000个数就产生一个更新事件
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//设置时钟分割 TIM_CKD_DIV1=0x0000,不分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ;//设置计数器模式为向上计数模式
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);//将配置应用到TIM6中
	TIM_UpdateRequestConfig( TIM6, TIM_UpdateSource_Regular);
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);//使能中断
	
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM6中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	
	TIM_Cmd(TIM6, ENABLE);//使能计数器
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//使能PORTD时钟
}

void TIM6_IRQHandler(void) 
{  
	//检测是否发生溢出更新事件
	if(TIM_GetITStatus(TIM6, TIM_IT_Update)== SET)
	{
//		printf("%d\r\n\r\n",ENEMY_CRITICAL);	
//		printf("%d\r\n\r\n",MARGIN_CRITICAL);	
		
		#ifdef SER_AD_VALUE_12 
		printf("ADCvalue[0]=%4d  ADCvalue[1]=%4d  ADCvalue[2]=%4d  ADCvalue[3]=%4d\r\n",ADCvalue[0],ADCvalue[1],ADCvalue[2],ADCvalue[3]);
//		printf("ADCvalue[4]=%4d  ADCvalue[5]=%4d  ADCvalue[6]=%4d  ADCvalue[7]=%4d\r\n",ADCvalue[4],ADCvalue[5],ADCvalue[6],ADCvalue[7]);
//		printf("ADCvalue[8]=%4d  ADCvalue[9]=%4d  ADCvalue[A]=%4d  ADCvalue[B]=%4d\r\n",ADCvalue[8],ADCvalue[9],ADCvalue[10],ADCvalue[11]);
		printf("\r\n\r\n");
		#endif
		
	
		/*************************检测地面的4个传感器*****************************************/
		
		if(ADCvalue[0]<BACK_MARGIN_CRITICAL)		{Flag_Margin|=0x01;	//左后方传感器（危险）
			Table_Count[0]=MARK_TIME_T;
			#ifdef SER_DANGER_T 
			printf("9号传感器检测到地面\r\n\r\n");	
			#endif
		}
		else if(ADCvalue[0]>=BACK_MARGIN_CRITICAL)Flag_Margin&=~0x01; //左后方传感器（安全）
		
		if(ADCvalue[1]<BACK_MARGIN_CRITICAL)		{Flag_Margin|=0x02;		 //右后方传感器（危险）
			Table_Count[1]=MARK_TIME_T;
			#ifdef SER_DANGER_T 
			printf("10号传感器检测到地面\r\n\r\n");	
			#endif
		}
		else if(ADCvalue[1]>=BACK_MARGIN_CRITICAL)Flag_Margin&=~0x02; //右后方传感器（安全）
		
		if(ADCvalue[2]<FRONT_MARGIN_CRITICAL)	 {Flag_Margin|=0x04;		 //左前方传感器（危险）
			Table_Count[2]=MARK_TIME_T;
			#ifdef SER_DANGER_T 
			printf("11号传感器检测到地面\r\n\r\n");	
			#endif
		}
		else if(ADCvalue[2]>=FRONT_MARGIN_CRITICAL)Flag_Margin&=~0x04;//左前方传感器（安全）
		
		if(ADCvalue[3]<FRONT_MARGIN_CRITICAL) 	 {Flag_Margin|=0x08;		 //右前方传感器（危险）
			Table_Count[3]=MARK_TIME_T;
			#ifdef SER_DANGER_T 
			printf("12号传感器检测到地面\r\n\r\n");	
			#endif
		}
		else if(ADCvalue[3]>=FRONT_MARGIN_CRITICAL)Flag_Margin&=~0x08;//右前方传感器（安全）
		/******************  (￣▽￣)~ ********* (⊙?⊙) ********* <(￣︶￣)>   ******************/
			if(SENSOR_LEFT==0)			 {Flag_Size|=0x01; //左面的传感器（危险）
					Enemy_Count[8]=MARK_TIME;
					#ifdef SER_DANGER 
				printf("13号传感器检测到敌人\r\n\r\n");	
				#endif
			}
			else if(SENSOR_LEFT==1) Flag_Size&=~0x01;//左面的传感器（安全）
			
			if(SENSOR_RIGHT==0)			 {Flag_Size|=0x02; //左面的传感器（危险）
					Enemy_Count[9]=MARK_TIME;
					#ifdef SER_DANGER 
				printf("14号传感器检测到敌人\r\n\r\n");	
				#endif
			}
			else if(SENSOR_RIGHT==1) Flag_Size&=~0x02;//右面的传感器（安全）
			
		if(Enemy_Count[0]>0)	Enemy_Count[0]--;
		if(Enemy_Count[1]>0)	Enemy_Count[1]--;
		if(Enemy_Count[2]>0)	Enemy_Count[2]--;
		if(Enemy_Count[3]>0)	Enemy_Count[3]--;
		if(Enemy_Count[4]>0)	Enemy_Count[4]--;
		if(Enemy_Count[5]>0)	Enemy_Count[5]--;
		if(Enemy_Count[6]>0)	Enemy_Count[6]--;
		if(Enemy_Count[7]>0)	Enemy_Count[7]--;
		if(Enemy_Count[8]>0)	Enemy_Count[8]--;
		if(Enemy_Count[9]>0)	Enemy_Count[9]--;
			
		if(Table_Count[0]>0)	Table_Count[0]--;
		if(Table_Count[1]>0)	Table_Count[1]--;
		if(Table_Count[2]>0)	Table_Count[2]--;
		if(Table_Count[3]>0)	Table_Count[3]--;
				
	if(delay_var_0.Allow_SoftTimer==1)
	{
		if(delay_var_0.SoftTimerCounter<15)	delay_var_0.SoftTimerCounter++;
		else 		{delay_var_0.Allow_SoftTimer=0;delay_var_0.SoftTimerCounter=0;}
	}	
	if(delay_var_1.Allow_SoftTimer==1)
	{
		if(delay_var_1.SoftTimerCounter<15)	delay_var_1.SoftTimerCounter++;
		else 		{delay_var_1.Allow_SoftTimer=0;delay_var_1.SoftTimerCounter=0;}
	}	
	if(delay_var_2.Allow_SoftTimer==1)
	{
		if(delay_var_2.SoftTimerCounter<15)	delay_var_2.SoftTimerCounter++;
		else 		{delay_var_2.Allow_SoftTimer=0;delay_var_2.SoftTimerCounter=0;}
	}	
	if(delay_var_3.Allow_SoftTimer==1)
	{
		if(delay_var_3.SoftTimerCounter<15)	delay_var_3.SoftTimerCounter++;
		else 		{delay_var_3.Allow_SoftTimer=0;delay_var_3.SoftTimerCounter=0;}
	}	
	
	
	}
	TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);
}

	

