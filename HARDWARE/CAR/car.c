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
	
		
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //PC2  ���ʹ��IO
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.2
 GPIO_ResetBits(GPIOC,GPIO_Pin_2);						 //PC.2 ����ͣ�ʹ��������

}

//TIM5 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM5_PWM_Init(u16 arr,u16 psc)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5  | RCC_APB2Periph_AFIO, ENABLE);	//ʹ�ܶ�ʱ��2ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO�����ģ��ʱ��

	TIM5_GPIO_Config(); 

   //��ʼ��TIM5
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	
	//��ʼ��TIM5 Channel1,2,3��4 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ը�
	
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM2 OC1
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR1�ϵ�Ԥװ�ؼĴ���
	
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);  //����ָ���Ĳ�����ʼ������TIM2 OC2
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR2�ϵ�Ԥװ�ؼĴ���
	
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM2 OC3
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR3�ϵ�Ԥװ�ؼĴ���
	
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);  //����ָ���Ĳ�����ʼ������TIM2 OC4
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR4�ϵ�Ԥװ�ؼĴ���
	
	TIM_ARRPreloadConfig(TIM5, ENABLE);			 // ʹ��TIM5���ؼĴ���ARR
	TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM5
	
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
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ�ܶ�ʱ��4ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	
	GPIO_PinRemapConfig(GPIO_Remap_TIM4, DISABLE); //Timer4������ӳ��  TIM4_CH3->PB8    
 
   //���ø�����Ϊ�����������,���TIM4 CH3��PWM���岨��	GPIOB.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
	
 //���ø�����Ϊ�����������,���TIM3 CH4��PWM���岨��	GPIOB.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM4 Channel3��4 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC3
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR3�ϵ�Ԥװ�ؼĴ���
	
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //����ָ���Ĳ�����ʼ������TIM4 OC4
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR4�ϵ�Ԥװ�ؼĴ���
	
 
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4
	
	TIM_SetCompare3(TIM4,1000);
 	TIM_SetCompare4(TIM4,1000);	
}
//ռ�ձȲ��ô���4500*0.98=4410.   
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

