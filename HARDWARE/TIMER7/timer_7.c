#include "timer_7.h" 
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "config.h"

enum {ENEMY_1 = 0, ENEMY_0 = !ENEMY_1};

#define RIGH_FRONT_1_PIN	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)//��ǰ1
#define RIGH_FRONT_2_PIN	GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//��ǰ2
#define LEFT_FRONT_2_PIN	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//��ǰ2
#define LEFT_FRONT_1_PIN	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//��ǰ1
#define LEFT_AFTER_1_PIN	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//���1
#define LEFT_AFTER_2_PIN	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//���2	
#define RIGH_AFTER_2_PIN	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//�Һ�2
#define RIGH_AFTER_1_PIN	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)//�Һ�1



//#define MARGIN_CRITICAL 2000  //����Ե��������̨�ϵ���Сֵ����̨�µ����ֵ�ĺ�һ�루  ��̨ʱֵ����С��
#define ENEMY_CRITICAL  600  //�����˴�����Σ��ʱ����Сֵ�Ͱ�ȫʱ�����ֵ�ĺ�һ�루��Σ��ʱֵ�������

#define ADJUSTMENT_0  (-350)	//��ǰ1
#define ADJUSTMENT_1  (-50)		//��ǰ2		
#define ADJUSTMENT_2  (-50)		//��ǰ2
#define ADJUSTMENT_3  (-50)		//��ǰ1
#define ADJUSTMENT_4  (-150)		//���1   50->100
#define ADJUSTMENT_5  (-1650)	//���2
#define ADJUSTMENT_6  (-200)	//�Һ�2
#define ADJUSTMENT_7  (-100)		//�Һ�1

//#define MARGIN_CRITICAL Margin_Critcal  //����Ե��������̨�ϵ���Сֵ����̨�µ����ֵ�ĺ�һ�루  ��̨ʱֵ����С��
//#define ENEMY_CRITICAL  Enemy_Critical  //�����˴�����Σ��ʱ����Сֵ�Ͱ�ȫʱ�����ֵ�ĺ�һ�루��Σ��ʱֵ�������


extern u32 Enemy_Count[10];
u8 Flag_Enemy=0x00;
u8 Temp_Flag_Enemy=0x00;
u8 Flag_Enemy_Count[8]={0};
u8 Flag_Count=0;
#define COUNT_ENEMY 20

u16 Enemy_Critical=(2900+ 500)/2;

extern __IO uint16_t ADCvalue[4];

//*****������ʱ��7��ʼ��*********
void TIM7_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);	
	
	TIM_TimeBaseStructure.TIM_Prescaler = 20 - 1;//Ԥ��Ƶϵ��Ϊ36000-1������������ʱ��Ϊ72MHz/36000 = 2kHz
	TIM_TimeBaseStructure.TIM_Period = 7200 - 1;//���ü��������С��ÿ��2000�����Ͳ���һ�������¼�
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����ʱ�ӷָ� TIM_CKD_DIV1=0x0000,���ָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up ;//���ü�����ģʽΪ���ϼ���ģʽ
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);//������Ӧ�õ�TIM7��
	TIM_UpdateRequestConfig( TIM7, TIM_UpdateSource_Regular);
	
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);//ʹ���ж�
	
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
	
	TIM_Cmd(TIM7, ENABLE);//ʹ�ܼ�����
}

void TIM7_IRQHandler(void) 
{
//����Ƿ�����������¼�
	if(TIM_GetITStatus(TIM7, TIM_IT_Update)== SET)
	{
		if(Flag_Count<=COUNT_ENEMY)
		{
			/*************************���ǰ����˵�8��������*****************************************/
		if(RIGH_FRONT_1_PIN==ENEMY_1)			 Flag_Enemy_Count[0]++; //ǰ�� 1 ��������Σ�գ�
		//else if(ADCvalue[0]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x01;//ǰ�� 1 ����������ȫ��
		
		if(RIGH_FRONT_2_PIN==ENEMY_1)			 Flag_Enemy_Count[1]++; //ǰ�� 2 ��������Σ�գ�
		//else if(ADCvalue[1]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x02;//ǰ�� 2 ����������ȫ��
		
		if(LEFT_FRONT_2_PIN==ENEMY_1)			 Flag_Enemy_Count[2]++; //ǰ�� 2 ��������Σ�գ�
		//else if(ADCvalue[2]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x04;//ǰ�� 2 ����������ȫ��
		
		if(LEFT_FRONT_1_PIN==ENEMY_1)			 Flag_Enemy_Count[3]++; //ǰ�� 1 ��������Σ�գ�
		//else if(ADCvalue[3]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x08;//ǰ�� 1 ����������ȫ��
		
		if(LEFT_AFTER_1_PIN==ENEMY_1)			 Flag_Enemy_Count[4]++; //���� 1 ��������Σ�գ�
		//else if(ADCvalue[4]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x10;//���� 1 ����������ȫ��
		
		if(LEFT_AFTER_2_PIN==ENEMY_1)			 Flag_Enemy_Count[5]++; //���� 2 ��������Σ�գ�
		//else if(ADCvalue[5]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x20;//���� 2 ����������ȫ��
		
		if(RIGH_AFTER_2_PIN==ENEMY_1)		   Flag_Enemy_Count[6]++; //���� 2 ��������Σ�գ�
		//else if(ADCvalue[6]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x40;//���� 2 ����������ȫ��
		
		if(RIGH_AFTER_1_PIN==ENEMY_1)			 Flag_Enemy_Count[7]++; //���� 1 ��������Σ�գ�
		//else if(ADCvalue[7]<=ENEMY_CRITICAL) Temp_Flag_Enemy&=~0x80;//���� 1 ����������ȫ��
		/******************  (������)~ ********* (��?��) ********* <(�����)>   ******************/
	
		Flag_Count++;
	}
	else if(Flag_Count>COUNT_ENEMY)
	{
		/*************************���ǰ����˵�8��������*****************************************/
//		if(RIGH_FRONT_1_PIN==ENEMY_1)			 {
//			if(Flag_Enemy_Count[0]>COUNT_ENEMY)	{Flag_Enemy|=0x01; //ǰ�� 1 ��������Σ�գ�
//			
//				Enemy_Count[0]=MARK_TIME;								
//				#ifdef SER_DANGER 
//			printf("1�Ŵ�������⵽����\r\n\r\n");	
//			#endif
//			}
//			else                      Flag_Enemy&=~0x01; //ǰ�� 1 ����������ȫ��
//		}
//		else if(RIGH_FRONT_1_PIN==ENEMY_0) Flag_Enemy&=~0x01;//ǰ�� 1 ����������ȫ��
		
		if(RIGH_FRONT_2_PIN==ENEMY_1)			 {
			if(Flag_Enemy_Count[1]>COUNT_ENEMY)	{Flag_Enemy|=0x02; //ǰ�� 2 ��������Σ�գ�
				Enemy_Count[1]=MARK_TIME;
				#ifdef SER_DANGER 
			printf("2�Ŵ�������⵽����\r\n\r\n");	
			#endif
			}
			else                      Flag_Enemy&=~0x02; //ǰ�� 2 ����������ȫ��
		}
		else if(RIGH_FRONT_2_PIN==ENEMY_0) Flag_Enemy&=~0x02;//ǰ�� 2 ����������ȫ��
		
		if(LEFT_FRONT_2_PIN==ENEMY_1)			 {
			if(Flag_Enemy_Count[2]>COUNT_ENEMY)	{Flag_Enemy|=0x04; //ǰ�� 2 ��������Σ�գ�
			
			Enemy_Count[2]=MARK_TIME;
				#ifdef SER_DANGER 
			printf("3�Ŵ�������⵽����\r\n\r\n");	
			#endif
		}
			else                      Flag_Enemy&=~0x04; //ǰ�� 2 ����������ȫ��
		}
		else if(LEFT_FRONT_2_PIN==ENEMY_0) Flag_Enemy&=~0x04;//ǰ�� 2 ����������ȫ��
		
//		if(LEFT_FRONT_1_PIN==ENEMY_1)			 {
//			if(Flag_Enemy_Count[3]>COUNT_ENEMY)	{Flag_Enemy|=0x08; //ǰ�� 1 ��������Σ�գ�
//			
//			Enemy_Count[3]=MARK_TIME;
//				#ifdef SER_DANGER 
//			printf("4�Ŵ�������⵽����\r\n\r\n");	
//			#endif
//			}
//			else                      Flag_Enemy&=~0x08; //ǰ�� 1 ����������ȫ��
//		}
//		else if(LEFT_FRONT_1_PIN==ENEMY_0) Flag_Enemy&=~0x08;//ǰ�� 1 ����������ȫ��
		
//		if(LEFT_AFTER_1_PIN==ENEMY_1)			 {
//			if(Flag_Enemy_Count[4]>COUNT_ENEMY)	{Flag_Enemy|=0x10; //���� 1 ��������Σ�գ�
//			
//				Enemy_Count[4]=MARK_TIME;
//				#ifdef SER_DANGER 
//			printf("5�Ŵ�������⵽����\r\n\r\n");	
//			#endif
//			}
//			else                      Flag_Enemy&=~0x10; //���� 1 ����������ȫ��
//		}
//		else if(LEFT_AFTER_1_PIN==ENEMY_0) Flag_Enemy&=~0x10;//���� 1 ����������ȫ��
		
		if(LEFT_AFTER_2_PIN==ENEMY_1)			 {
			if(Flag_Enemy_Count[5]>COUNT_ENEMY)	{Flag_Enemy|=0x20; //���� 2 ��������Σ�գ�
			Enemy_Count[5]=MARK_TIME;
				#ifdef SER_DANGER 
			printf("6�Ŵ�������⵽����\r\n\r\n");	
			#endif
			}
			else                      Flag_Enemy&=~0x20; //���� 2 ����������ȫ��
		}
		else if(LEFT_AFTER_2_PIN==ENEMY_0) Flag_Enemy&=~0x20;//���� 2 ����������ȫ��
		
		if(RIGH_AFTER_2_PIN==ENEMY_1)		   {
			if(Flag_Enemy_Count[6]>COUNT_ENEMY)	{Flag_Enemy|=0x40; //���� 2 ��������Σ�գ�
			Enemy_Count[6]=MARK_TIME;
				#ifdef SER_DANGER 
			printf("7�Ŵ�������⵽���� \r\n\r\n");	
			#endif
			}
			else                      Flag_Enemy&=~0x40; //���� 2 ����������ȫ��
		}
		else if(RIGH_AFTER_2_PIN==ENEMY_0) Flag_Enemy&=~0x40;//���� 2 ����������ȫ��
		
//		if(RIGH_AFTER_1_PIN==ENEMY_1)			 {
//			if(Flag_Enemy_Count[7]>COUNT_ENEMY)	{Flag_Enemy|=0x80; //���� 1 ��������Σ�գ�
//			Enemy_Count[7]=MARK_TIME;
//				#ifdef SER_DANGER 
//			printf("8�Ŵ�������⵽����\r\n\r\n");	
//			#endif
//			}
//			else                      Flag_Enemy&=~0x80; //���� 1 ����������ȫ��
//		}
//		else if(RIGH_AFTER_1_PIN==ENEMY_0) Flag_Enemy&=~0x80;//���� 1 ����������ȫ��
		/******************  (������)~ ********* (��?��) ********* <(�����)>   ******************/
		
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


