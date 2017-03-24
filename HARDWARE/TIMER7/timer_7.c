#include "timer_7.h" 
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "config.h"

enum {ENEMY_1 = 0, ENEMY_0 = !ENEMY_1};

#define RIGH_FRONT_1_PIN	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)//右前1
#define RIGH_FRONT_2_PIN	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//右前2
#define LEFT_FRONT_2_PIN	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//左前2
#define LEFT_FRONT_1_PIN	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//左前1
#define LEFT_AFTER_1_PIN	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//左后1
#define LEFT_AFTER_2_PIN	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//左后2	
#define RIGH_AFTER_2_PIN	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//右后2
#define RIGH_AFTER_1_PIN	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)//右后1



//#define MARGIN_CRITICAL 2000  //检测边缘传感器在台上的最小值和在台下的最大值的和一半（  出台时值则会减小）
#define ENEMY_CRITICAL  600  //检测敌人传感器危险时的最小值和安全时的最大值的和一半（有危险时值则会增大）

#define ADJUSTMENT_0  (-350)	//右前1
#define ADJUSTMENT_1  (-50)		//右前2		
#define ADJUSTMENT_2  (-50)		//左前2
#define ADJUSTMENT_3  (-50)		//左前1
#define ADJUSTMENT_4  (-150)		//左后1   50->100
#define ADJUSTMENT_5  (-1650)	//左后2
#define ADJUSTMENT_6  (-200)	//右后2
#define ADJUSTMENT_7  (-100)		//右后1

//#define MARGIN_CRITICAL Margin_Critcal  //检测边缘传感器在台上的最小值和在台下的最大值的和一半（  出台时值则会减小）
//#define ENEMY_CRITICAL  Enemy_Critical  //检测敌人传感器危险时的最小值和安全时的最大值的和一半（有危险时值则会增大）


extern u32 Enemy_Count[10];
u8 Flag_Enemy=0x00;
u8 Temp_Flag_Enemy=0x00;
u8 Flag_Enemy_Count[8]={0};
u8 Flag_Count=0;
#define COUNT_ENEMY 20

u16 Enemy_Critical=(2900+ 500)/2;

extern __IO uint16_t ADCvalue[4];

//*****基本定时器7初始化*********
void TIM7_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);	
	
	TIM_TimeBaseStructure.TIM_Prescaler = 20 - 1;//预分频系数为36000-1，这样计数器时钟为72MHz/36000 = 2kHz
	TIM_TimeBaseStructure.TIM_Period = 7200 - 1;//设置计数溢出大小，每计2000个数就产生一个更新事件
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//设置时钟分割 TIM_CKD_DIV1=0x0000,不分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ;//设置计数器模式为向上计数模式
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);//将配置应用到TIM7中
	TIM_UpdateRequestConfig( TIM7, TIM_UpdateSource_Regular);
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);//使能中断
	
	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM6中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
	
	TIM_Cmd(TIM7, ENABLE);//使能计数器
}

void TIM7_IRQHandler(void) 
{
//检测是否发生溢出更新事件
	if(TIM_GetITStatus(TIM7, TIM_IT_Update)== SET)
	{
		if(Flag_Count<=COUNT_ENEMY)
		{
			/*************************检测前后敌人的8个传感器*****************************************/
		if(RIGH_FRONT_1_PIN==ENEMY_1)			 Flag_Enemy_Count[0]++; //前右 1 传感器（危险）
		//else if(ADCvalue[0]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x01;//前右 1 传感器（安全）
		
		if(RIGH_FRONT_2_PIN==ENEMY_1)			 Flag_Enemy_Count[1]++; //前右 2 传感器（危险）
		//else if(ADCvalue[1]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x02;//前右 2 传感器（安全）
		
		if(LEFT_FRONT_2_PIN==ENEMY_1)			 Flag_Enemy_Count[2]++; //前左 2 传感器（危险）
		//else if(ADCvalue[2]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x04;//前左 2 传感器（安全）
		
		if(LEFT_FRONT_1_PIN==ENEMY_1)			 Flag_Enemy_Count[3]++; //前左 1 传感器（危险）
		//else if(ADCvalue[3]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x08;//前左 1 传感器（安全）
		
		if(LEFT_AFTER_1_PIN==ENEMY_1)			 Flag_Enemy_Count[4]++; //后左 1 传感器（危险）
		//else if(ADCvalue[4]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x10;//后左 1 传感器（安全）
		
		if(LEFT_AFTER_2_PIN==ENEMY_1)			 Flag_Enemy_Count[5]++; //后左 2 传感器（危险）
		//else if(ADCvalue[5]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x20;//后左 2 传感器（安全）
		
		if(RIGH_AFTER_2_PIN==ENEMY_1)		   Flag_Enemy_Count[6]++; //后右 2 传感器（危险）
		//else if(ADCvalue[6]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x40;//后右 2 传感器（安全）
		
		if(RIGH_AFTER_1_PIN==ENEMY_1)			 Flag_Enemy_Count[7]++; //后右 1 传感器（危险）
		//else if(ADCvalue[7]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x80;//后右 1 传感器（安全）
		/******************  (￣▽￣)~ ********* (⊙?⊙) ********* <(￣︶￣)>   ******************/
	
		Flag_Count++;
	}
	else if(Flag_Count>COUNT_ENEMY)
	{
		/*************************检测前后敌人的8个传感器*****************************************/
//		if(RIGH_FRONT_1_PIN==ENEMY_1)			 {
//			if(Flag_Enemy_Count[0]>COUNT_ENEMY)	{Flag_Enemy|=0x01; //前右 1 传感器（危险）
//			
//				Enemy_Count[0]=MARK_TIME;								
//				#ifdef SER_DANGER 
//			printf("1号传感器检测到敌人\r\n\r\n");	
//			#endif
//			}
//			else                      Flag_Enemy&=~0x01; //前右 1 传感器（安全）
//		}
//		else if(RIGH_FRONT_1_PIN==ENEMY_0) Flag_Enemy&=~0x01;//前右 1 传感器（安全）
		
		if(RIGH_FRONT_2_PIN==ENEMY_1)			 {
			if(Flag_Enemy_Count[1]>COUNT_ENEMY)	{Flag_Enemy|=0x02; //前右 2 传感器（危险）
				Enemy_Count[1]=MARK_TIME;
				#ifdef SER_DANGER 
			printf("2号传感器检测到敌人\r\n\r\n");	
			#endif
			}
			else                      Flag_Enemy&=~0x02; //前右 2 传感器（安全）
		}
		else if(RIGH_FRONT_2_PIN==ENEMY_0) Flag_Enemy&=~0x02;//前右 2 传感器（安全）
		
		if(LEFT_FRONT_2_PIN==ENEMY_1)			 {
			if(Flag_Enemy_Count[2]>COUNT_ENEMY)	{Flag_Enemy|=0x04; //前左 2 传感器（危险）
			
			Enemy_Count[2]=MARK_TIME;
				#ifdef SER_DANGER 
			printf("3号传感器检测到敌人\r\n\r\n");	
			#endif
		}
			else                      Flag_Enemy&=~0x04; //前左 2 传感器（安全）
		}
		else if(LEFT_FRONT_2_PIN==ENEMY_0) Flag_Enemy&=~0x04;//前左 2 传感器（安全）
		
//		if(LEFT_FRONT_1_PIN==ENEMY_1)			 {
//			if(Flag_Enemy_Count[3]>COUNT_ENEMY)	{Flag_Enemy|=0x08; //前左 1 传感器（危险）
//			
//			Enemy_Count[3]=MARK_TIME;
//				#ifdef SER_DANGER 
//			printf("4号传感器检测到敌人\r\n\r\n");	
//			#endif
//			}
//			else                      Flag_Enemy&=~0x08; //前左 1 传感器（安全）
//		}
//		else if(LEFT_FRONT_1_PIN==ENEMY_0) Flag_Enemy&=~0x08;//前左 1 传感器（安全）
		
//		if(LEFT_AFTER_1_PIN==ENEMY_1)			 {
//			if(Flag_Enemy_Count[4]>COUNT_ENEMY)	{Flag_Enemy|=0x10; //后左 1 传感器（危险）
//			
//				Enemy_Count[4]=MARK_TIME;
//				#ifdef SER_DANGER 
//			printf("5号传感器检测到敌人\r\n\r\n");	
//			#endif
//			}
//			else                      Flag_Enemy&=~0x10; //后左 1 传感器（安全）
//		}
//		else if(LEFT_AFTER_1_PIN==ENEMY_0) Flag_Enemy&=~0x10;//后左 1 传感器（安全）
		
		if(LEFT_AFTER_2_PIN==ENEMY_1)			 {
			if(Flag_Enemy_Count[5]>COUNT_ENEMY)	{Flag_Enemy|=0x20; //后左 2 传感器（危险）
			Enemy_Count[5]=MARK_TIME;
				#ifdef SER_DANGER 
			printf("6号传感器检测到敌人\r\n\r\n");	
			#endif
			}
			else                      Flag_Enemy&=~0x20; //后左 2 传感器（安全）
		}
		else if(LEFT_AFTER_2_PIN==ENEMY_0) Flag_Enemy&=~0x20;//后左 2 传感器（安全）
		
		if(RIGH_AFTER_2_PIN==ENEMY_1)		   {
			if(Flag_Enemy_Count[6]>COUNT_ENEMY)	{Flag_Enemy|=0x40; //后右 2 传感器（危险）
			Enemy_Count[6]=MARK_TIME;
				#ifdef SER_DANGER 
			printf("7号传感器检测到敌人 \r\n\r\n");	
			#endif
			}
			else                      Flag_Enemy&=~0x40; //后右 2 传感器（安全）
		}
		else if(RIGH_AFTER_2_PIN==ENEMY_0) Flag_Enemy&=~0x40;//后右 2 传感器（安全）
		
//		if(RIGH_AFTER_1_PIN==ENEMY_1)			 {
//			if(Flag_Enemy_Count[7]>COUNT_ENEMY)	{Flag_Enemy|=0x80; //后右 1 传感器（危险）
//			Enemy_Count[7]=MARK_TIME;
//				#ifdef SER_DANGER 
//			printf("8号传感器检测到敌人\r\n\r\n");	
//			#endif
//			}
//			else                      Flag_Enemy&=~0x80; //后右 1 传感器（安全）
//		}
//		else if(RIGH_AFTER_1_PIN==ENEMY_0) Flag_Enemy&=~0x80;//后右 1 传感器（安全）
		/******************  (￣▽￣)~ ********* (⊙?⊙) ********* <(￣︶￣)>   ******************/
		
		Flag_Enemy_Count[0]=0;
		Flag_Enemy_Count[1]=0;
		Flag_Enemy_Count[2]=0;
		Flag_Enemy_Count[3]=0;
		Flag_Enemy_Count[4]=0;
		Flag_Enemy_Count[5]=0;
		Flag_Enemy_Count[6]=0;
		Flag_Enemy_Count[7]=0;
		
		Flag_Count=0;
			
		}
	}
	TIM_ClearITPendingBit(TIM7 , TIM_FLAG_Update);
}


