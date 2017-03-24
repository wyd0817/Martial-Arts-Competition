#include "car.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include<math.h>
//////////////////////////////////////////////////////////////////////////////////	 

u8 Flag_Forward=1;
int Left_Speed=0,Right_Speed=0;

void TIM5_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOA Configuration: Channel 1,4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //PC2  电机使能IO
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC.2
 GPIO_ResetBits(GPIOC,GPIO_Pin_2);						 //PC.2 输出低（使能驱动）

}

//TIM5 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM5_PWM_Init(u16 arr,u16 psc)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5  | RCC_APB2Periph_AFIO, ENABLE);	//使能定时器2时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);  //使能GPIO外设和模块时钟

	TIM5_GPIO_Config(); 

   //初始化TIM5
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	
	//初始化TIM5 Channel1,2,3，4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高
	
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC1
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM2在CCR1上的预装载寄存器
	
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIM2 OC2
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM2在CCR2上的预装载寄存器
	
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC3
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM2在CCR3上的预装载寄存器
	
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIM2 OC4
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM2在CCR4上的预装载寄存器
	
	TIM_ARRPreloadConfig(TIM5, ENABLE);			 // 使能TIM5重载寄存器ARR
	TIM_Cmd(TIM5, ENABLE);  //使能TIM5
	
	TIM_SetCompare1(TIM5,0000);
 	TIM_SetCompare2(TIM5,0000);	
	TIM_SetCompare3(TIM5,0000);
 	TIM_SetCompare4(TIM5,0000);	
	
}

void TIM4_PWM_Init(u16 arr,u16 psc)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定时器4时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	GPIO_PinRemapConfig(GPIO_Remap_TIM4, DISABLE); //Timer4部分重映射  TIM4_CH3->PB8    
 
   //设置该引脚为复用输出功能,输出TIM4 CH3的PWM脉冲波形	GPIOB.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
	
 //设置该引脚为复用输出功能,输出TIM3 CH4的PWM脉冲波形	GPIOB.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM4 Channel3，4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC3
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR3上的预装载寄存器
	
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据指定的参数初始化外设TIM4 OC4
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM1在CCR4上的预装载寄存器
	
 
	TIM_Cmd(TIM4, ENABLE);  //使能TIM4
	
	TIM_SetCompare3(TIM4,1000);
 	TIM_SetCompare4(TIM4,1000);	
}
//占空比不得大于4500*0.98=4410.   
//PB9(A IN1),PA11(A IN2),
//PB8(B IN1),PA8(B IN2)
 void Car_Forward(u16 speed_0)
{
	if(Flag_Forward==0)   {Car_Pause();/*delay_ms(10);*/}
 	TIM_SetCompare1(TIM5,0000);//PB9 (A IN1)
	TIM_SetCompare2(TIM5,speed_0);//PA11(A IN2)
	TIM_SetCompare4(TIM5,0000);//PB8 (B IN1)
	TIM_SetCompare3(TIM5,speed_0);//PA8 (B IN2) 
	Flag_Forward=1;
	Left_Speed=speed_0;
	Right_Speed=speed_0;
}
void Car_Back(u16 speed_1)
{	
	if(Flag_Forward==1)   {Car_Pause();/*delay_ms(10);*/}
	TIM_SetCompare1(TIM5,speed_1);//PB9 (A IN1)
	TIM_SetCompare2(TIM5,0000);//PA11(A IN2)
	TIM_SetCompare4(TIM5,speed_1);//PB8 (B IN1)
	TIM_SetCompare3(TIM5,0000);//PA8 (B IN2) 
	Flag_Forward=0;
	Left_Speed=(-speed_1);
	Right_Speed=(-speed_1);
}
void Car_Pause(void)
{
//	u16 Temp_Pause,Temp_Left_Speed,Temp_Right_Speed;
//	
//	Temp_Left_Speed=fabs(Left_Speed);
//	Temp_Right_Speed=fabs(Right_Speed);
//			
//	for(Temp_Pause=1;Temp_Pause<=100;Temp_Pause++)
//	{
//		if(Temp_Left_Speed>10)
//			Temp_Left_Speed-=10;
//		else 
//			Temp_Left_Speed=0;
//		if(Temp_Right_Speed>10)
//			Temp_Right_Speed-=10;
//		else 
//			Temp_Right_Speed=0;
//		Temp_Left_Speed=0;
//		Temp_Right_Speed=0;
//		if(Left_Speed>0)
//		{
//			TIM_SetCompare1(TIM5,0000);//PB9 (A IN1)
//			TIM_SetCompare2(TIM5,Temp_Left_Speed);//PA11(A IN2)
//		}
//		else 
//		{
//			TIM_SetCompare1(TIM5,Temp_Left_Speed);//PB9 (A IN1)
//			TIM_SetCompare2(TIM5,0000);//PA11(A IN2)
//		}
//		if(Right_Speed>0)
//		{
//			TIM_SetCompare4(TIM5,0000);//PB9 (A IN1)
//			TIM_SetCompare3(TIM5,Temp_Right_Speed);//PA11(A IN2)
//		}
//		else 
//		{
//			TIM_SetCompare4(TIM5,Temp_Right_Speed);//PB9 (A IN1)
//			TIM_SetCompare3(TIM5,0000);//PA11(A IN2)
//		}
//		delay_us(1000);
//	}
	

	TIM_SetCompare1(TIM5,0000);//PB9 (A IN1)
	TIM_SetCompare2(TIM5,0000);//PA11(A IN2)
	TIM_SetCompare4(TIM5,0000);//PB8 (B IN1)
	TIM_SetCompare3(TIM5,0000);//PA8 (B IN2) 

}
void Car_Right_Back(u16 speed)
{
	if(Flag_Forward==1)   {Car_Pause();delay_ms(10);}
	TIM_SetCompare1(TIM5,speed);//PB9 (A IN1)
	TIM_SetCompare2(TIM5,0000);//PA11(A IN2)
	TIM_SetCompare4(TIM5,0000);//PB8 (B IN1)
	TIM_SetCompare3(TIM5,speed);//PA8 (B IN2) 
	Flag_Forward=0;
	Left_Speed=(-speed);
	Right_Speed=(+speed);
}
void Car_Left_Back(u16 speed)
{
	if(Flag_Forward==1)   {Car_Pause();delay_ms(10);}
	TIM_SetCompare1(TIM5,0000);//PB9 (A IN1)
	TIM_SetCompare2(TIM5,speed);//PA11(A IN2)
	TIM_SetCompare4(TIM5,speed);//PB8 (B IN1)
	TIM_SetCompare3(TIM5,0000);//PA8 (B IN2) 
	Flag_Forward=0;
	Left_Speed=(+speed);
	Right_Speed=(-speed);
}
void Car_Right_Forward(u16 speed)
{
	if(Flag_Forward==0)   {Car_Pause();delay_ms(10);}
	TIM_SetCompare1(TIM5,0000);//PB9 (A IN1)
	TIM_SetCompare2(TIM5,speed);//PA11(A IN2)
	TIM_SetCompare4(TIM5,speed);//PB8 (B IN1)
	TIM_SetCompare3(TIM5,0000);//PA8 (B IN2) 	
	Flag_Forward=1;
	Left_Speed=(+speed);
	Right_Speed=(-speed);
}
void Car_Left_Forward(u16 speed)
{
	if(Flag_Forward==0)   {Car_Pause();delay_ms(10);}
	TIM_SetCompare1(TIM5,speed);//PB9 (A IN1)
	TIM_SetCompare2(TIM5,0000);//PA11(A IN2)
	TIM_SetCompare4(TIM5,0000);//PB8 (B IN1)
	TIM_SetCompare3(TIM5,speed);//PA8 (B IN2) 
	Flag_Forward=1;
	Left_Speed=(-speed);
	Right_Speed=(+speed);
}

void Car_Right_Back_Chess(u16 speed)
{
	if(Flag_Forward==1)   {Car_Pause();delay_ms(10);}
	TIM_SetCompare4(TIM5,speed);//PB8 (B IN1)
	TIM_SetCompare3(TIM5,0000);//PA8 (B IN2) 
	Flag_Forward=0;
	Right_Speed=(-speed);
}
void Car_Left_Back_Chess(u16 speed)
{
	if(Flag_Forward==1)   {Car_Pause();delay_ms(10);}
	TIM_SetCompare1(TIM5,speed);//PB9 (A IN1)
	TIM_SetCompare2(TIM5,0000);//PA11(A IN2)
	Flag_Forward=0;
	Left_Speed=(-speed);
}
void Car_Right_Forward_Chess(u16 speed)
{
	if(Flag_Forward==0)   {Car_Pause();delay_ms(10);}
	TIM_SetCompare4(TIM5,0000);//PB8 (B IN1)
	TIM_SetCompare3(TIM5,speed);//PA8 (B IN2) 	
	Flag_Forward=1;
	Right_Speed=(+speed);
}
void Car_Left_Forward_Chess(u16 speed)
{
	if(Flag_Forward==0)   {Car_Pause();delay_ms(10);}
	TIM_SetCompare1(TIM5,0000);//PB9 (A IN1)
	TIM_SetCompare2(TIM5,speed);//PA11(A IN2)
	Flag_Forward=1;
	Left_Speed=(+speed);
}

