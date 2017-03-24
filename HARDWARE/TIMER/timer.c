#include "timer.h" 
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "config.h"
#include "bsp_init.h"

//#define MARGIN_CRITICAL Margin_Critcal  //����Ե��������̨�ϵ���Сֵ����̨�µ����ֵ�ĺ�һ�루  ��̨ʱֵ����С��
//#define ENEMY_CRITICAL  Enemy_Critical  //�����˴�����Σ��ʱ����Сֵ�Ͱ�ȫʱ�����ֵ�ĺ�һ�루��Σ��ʱֵ�������

//#define FRONT_MARGIN_CRITICAL 2000  //��Խ��Խ����  ��̨ʱֵ����С��
//#define BACK_MARGIN_CRITICAL 2000  // ��Խ��Խ����  ��̨ʱֵ����С��

#define FRONT_MARGIN_CRITICAL 1700  //��Խ��Խ����  ��̨ʱֵ����С��
#define BACK_MARGIN_CRITICAL 1700  // ��Խ��Խ����  ��̨ʱֵ����С��


//#define ENEMY_CRITICAL  600  //�����˴�����Σ��ʱ����Сֵ�Ͱ�ȫʱ�����ֵ�ĺ�һ�루��Σ��ʱֵ�������

u32 Enemy_Count[10]={0};
u32 Table_Count[4]={0};
u8 Flag_Margin=0x00;
u8 Flag_Size=0x00; 

u16 Margin_Critcal=1000;
//u16 Margin_Critcal=(3300+1500)/2;


extern __IO uint16_t ADCvalue[4];
extern delay_var delay_var_0,delay_var_1,delay_var_2,delay_var_3;

//*****������ʱ��6��ʼ��*********
void TIM6_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	
	
	TIM_TimeBaseStructure.TIM_Prescaler = 200 - 1;//Ԥ��Ƶϵ��Ϊ36000-1������������ʱ��Ϊ72MHz/36000 = 2kHz
	TIM_TimeBaseStructure.TIM_Period = 7200 - 1;//���ü��������С��ÿ��2000�����Ͳ���һ�������¼�
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����ʱ�ӷָ� TIM_CKD_DIV1=0x0000,���ָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ;//���ü�����ģʽΪ���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);//������Ӧ�õ�TIM6��
	TIM_UpdateRequestConfig( TIM6, TIM_UpdateSource_Regular);
	
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);//ʹ���ж�
	
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	
	TIM_Cmd(TIM6, ENABLE);//ʹ�ܼ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);//ʹ��PORTDʱ��
}

void TIM6_IRQHandler(void) 
{  
	//����Ƿ�����������¼�
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
		
	
		/*************************�������4��������*****************************************/
		
		if(ADCvalue[0]<BACK_MARGIN_CRITICAL)		{Flag_Margin|=0x01;	//��󷽴�������Σ�գ�
			Table_Count[0]=MARK_TIME_T;
			#ifdef SER_DANGER_T 
			printf("9�Ŵ�������⵽����\r\n\r\n");	
			#endif
		}
		else if(ADCvalue[0]>=BACK_MARGIN_CRITICAL)Flag_Margin&=~0x01; //��󷽴���������ȫ��
		
		if(ADCvalue[1]<BACK_MARGIN_CRITICAL)		{Flag_Margin|=0x02;		 //�Һ󷽴�������Σ�գ�
			Table_Count[1]=MARK_TIME_T;
			#ifdef SER_DANGER_T 
			printf("10�Ŵ�������⵽����\r\n\r\n");	
			#endif
		}
		else if(ADCvalue[1]>=BACK_MARGIN_CRITICAL)Flag_Margin&=~0x02; //�Һ󷽴���������ȫ��
		
		if(ADCvalue[2]<FRONT_MARGIN_CRITICAL)	 {Flag_Margin|=0x04;		 //��ǰ����������Σ�գ�
			Table_Count[2]=MARK_TIME_T;
			#ifdef SER_DANGER_T 
			printf("11�Ŵ�������⵽����\r\n\r\n");	
			#endif
		}
		else if(ADCvalue[2]>=FRONT_MARGIN_CRITICAL)Flag_Margin&=~0x04;//��ǰ������������ȫ��
		
		if(ADCvalue[3]<FRONT_MARGIN_CRITICAL) 	 {Flag_Margin|=0x08;		 //��ǰ����������Σ�գ�
			Table_Count[3]=MARK_TIME_T;
			#ifdef SER_DANGER_T 
			printf("12�Ŵ�������⵽����\r\n\r\n");	
			#endif
		}
		else if(ADCvalue[3]>=FRONT_MARGIN_CRITICAL)Flag_Margin&=~0x08;//��ǰ������������ȫ��
		/******************  (������)~ ********* (��?��) ********* <(�����)>   ******************/
			if(SENSOR_LEFT==0)			 {Flag_Size|=0x01; //����Ĵ�������Σ�գ�
					Enemy_Count[8]=MARK_TIME;
					#ifdef SER_DANGER 
				printf("13�Ŵ�������⵽����\r\n\r\n");	
				#endif
			}
			else if(SENSOR_LEFT==1) Flag_Size&=~0x01;//����Ĵ���������ȫ��
			
			if(SENSOR_RIGHT==0)			 {Flag_Size|=0x02; //����Ĵ�������Σ�գ�
					Enemy_Count[9]=MARK_TIME;
					#ifdef SER_DANGER 
				printf("14�Ŵ�������⵽����\r\n\r\n");	
				#endif
			}
			else if(SENSOR_RIGHT==1) Flag_Size&=~0x02;//����Ĵ���������ȫ��
			
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

	

