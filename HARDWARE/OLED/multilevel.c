#include "multilevel.h"
#include "oled.h"
#include "key.h"
#include "delay.h"
#include "stmflash.h"

 
extern u8 Flag_Margin;//�����̨̨���4��������(9-12)
extern u8 Flag_Enemy; //ǰ������˵�8��������(1-8)
extern u8 Flag_Size;  //��������˵�2��������(13-14)
	
//Ҫд�뵽STM32 FLASH���ַ�������
u16 TEXT_Buffer[2]={700,2000};
#define SIZE sizeof(TEXT_Buffer)	 			  	//���鳤��
#define FLASH_SAVE_ADDR  0X08030000 				//����FLASH �����ַ(����Ϊż��)
u16 datatemp[SIZE]={700,2000};

//u16 Temp_a=100,Temp_b=100;
u8 Get_key_up;
u8 Get_key_down;
u8 Get_key_enter;
u8 Get_key_exit;
u8 key_flag;
u8  func_index;
u8 temp_test=0;
u8 t;
void (*current_operation_index)(void); //��ǰ״̬Ӧ��ִ�еĲ���
typedef struct
{
	u8 current;//��ǰ״̬������
	u8 up; //����
	u8 down;	//����
	u8 enter; //ȷ��
	u8 exit; //�˳�
	void (*current_operation)(void); //��ǰ״̬Ӧ��ִ�еĲ���
} Menu_table;

Menu_table  table[5]=
{
	{0,0,0,1,0,(*fun0)},//��ʾ�Ƿ�Σ��  ����ʾ
	{1,0,2,3,1,(*fun1)},//��ʾ������1
	{2,0,2,4,1,(*fun2)},//��ʾ������2		
	{3,1,3,1,3,(*fun3)},//��ʾ��������1
	{4,2,4,2,4,(*fun4)},//��ʾ��������2
};
	

void  Menu_key_set(void)
{
		t=KEY_Scan(0);		//�õ���ֵ
	  if(t)
		{						   
			switch(t)
			{		
				case KEY_RIGHT:	//���Ʒ�����  
					if(func_index==3)  TEXT_Buffer[0]+=100;//�ڵ������水������
					if(func_index==4)  TEXT_Buffer[1]+=100;//�ڵ������水������
					OLED_Clear(0);
					OLED_Refresh_Gram(0);	
					func_index=table[func_index].down;    //���Ϸ�  
					break;
				case KEY_UP:	//����LED0��ת  
					OLED_Clear(0);
					OLED_Refresh_Gram(0);	
					func_index=table[func_index].up;//���·�
					break;
				case KEY_LEFT:	//����LED1��ת	  
					if(func_index==3||func_index==4)//�ڵ������水��ȷ��
					{
						STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
						datatemp[0]=TEXT_Buffer[0];
						datatemp[1]=TEXT_Buffer[1];
					}
					if(func_index==1||func_index==2)//��ѡ����水��ȷ��
					{
						STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
						TEXT_Buffer[0]=datatemp[0];
						TEXT_Buffer[1]=datatemp[1];
					}
					OLED_Clear(0);
					OLED_Refresh_Gram(0);					
						func_index=table[func_index].enter;//�س�
					break;
				case KEY_DOWN:	//ͬʱ����LED0,LED1��ת 
					if(func_index==1)  datatemp[0]=TEXT_Buffer[0];//��ѡ����水�ļ�С
					if(func_index==2)  datatemp[1]=TEXT_Buffer[1];//��ѡ����水�ļ�С
					if(func_index==3)  TEXT_Buffer[0]-=100;//�ڵ������水�ļ�С
					if(func_index==4)  TEXT_Buffer[1]-=100;//�ڵ������水�ļ�С
					OLED_Clear(0);
					OLED_Refresh_Gram(0);	
					func_index=table[func_index].exit;//�س�
					break;
		}
		}else delay_ms(10); 
		
	current_operation_index=table[func_index].current_operation;
	(*current_operation_index)();//ִ�е�ǰ��������
}

void  fun0(void)
{ 

	u8 j;
	u8 b;
	b=Flag_Margin;
	//��ʾ�Ƿ�Σ��
	for (j = 0; j < 4; j++)
	{
		if (b& 0x01)
		{
				OLED_ShowChar(8*j,0,'1',16,0,1);
				OLED_Refresh_Gram(1);
		}
		else
		{
			OLED_ShowChar(8*j,0,'0',16,0,1);
			OLED_Refresh_Gram(1);
		}
		b >>= 1;
	}
	
	b=Flag_Enemy;
	//��ʾ�Ƿ�Σ��
	for (j = 0; j < 8; j++)
	{
		if (b& 0x01)
		{
				OLED_ShowChar(8*j,0,'1',16,0,0);
				OLED_Refresh_Gram(0);
		}
		else
		{
			OLED_ShowChar(8*j,0,'0',16,0,0);
			OLED_Refresh_Gram(0);
		}
		b >>= 1;
	}
	
	b=Flag_Size;
	//��ʾ�Ƿ�Σ��
	for (j = 0; j < 2; j++)
	{
		if (b& 0x01)
		{
				OLED_ShowChar(64+8*j,0,'1',16,0,0);
				OLED_Refresh_Gram(0);
		}
		else
		{
			OLED_ShowChar(64+8*j,0,'0',16,0,0);
			OLED_Refresh_Gram(0);
		}
		b >>= 1;
	}
}
void  fun1(void)
{	
	//��ʾ������1
	OLED_ShowChinese_num(0,16,4,0,0);
	OLED_Refresh_Gram(0);
}

void  fun2(void)
{
	//��ʾ������2
	OLED_ShowChinese_num(0,16,4,1,0);
	OLED_Refresh_Gram(0);
}
void  fun3(void)
{
	//��ʾ��������1
	
	OLED_ShowNum(93,48,TEXT_Buffer[0],4,16,0);//��ʾASCII�ַ�����ֵ 
	OLED_Refresh_Gram(0);	
}
void  fun4(void)
{
 //��ʾ��������2
	OLED_ShowNum(93,48,TEXT_Buffer[1],4,16,0);//��ʾASCII�ַ�����ֵ 
	OLED_Refresh_Gram(0);
}





