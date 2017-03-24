#include "multilevel.h"
#include "oled.h"
#include "key.h"
#include "delay.h"
#include "stmflash.h"

 
extern u8 Flag_Margin;//检测擂台台面的4个传感器(9-12)
extern u8 Flag_Enemy; //前后检测敌人的8个传感器(1-8)
extern u8 Flag_Size;  //侧面检测敌人的2个传感器(13-14)
	
//要写入到STM32 FLASH的字符串数组
u16 TEXT_Buffer[2]={700,2000};
#define SIZE sizeof(TEXT_Buffer)	 			  	//数组长度
#define FLASH_SAVE_ADDR  0X08030000 				//设置FLASH 保存地址(必须为偶数)
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
void (*current_operation_index)(void); //当前状态应该执行的操作
typedef struct
{
	u8 current;//当前状态索引号
	u8 up; //向上
	u8 down;	//向下
	u8 enter; //确定
	u8 exit; //退出
	void (*current_operation)(void); //当前状态应该执行的操作
} Menu_table;

Menu_table  table[5]=
{
	{0,0,0,1,0,(*fun0)},//显示是否危险  总显示
	{1,0,2,3,1,(*fun1)},//显示主界面1
	{2,0,2,4,1,(*fun2)},//显示主界面2		
	{3,1,3,1,3,(*fun3)},//显示调整界面1
	{4,2,4,2,4,(*fun4)},//显示调整界面2
};
	

void  Menu_key_set(void)
{
		t=KEY_Scan(0);		//得到键值
	  if(t)
		{						   
			switch(t)
			{		
				case KEY_RIGHT:	//控制蜂鸣器  
					if(func_index==3)  TEXT_Buffer[0]+=100;//在调整界面按的增加
					if(func_index==4)  TEXT_Buffer[1]+=100;//在调整界面按的增加
					OLED_Clear(0);
					OLED_Refresh_Gram(0);	
					func_index=table[func_index].down;    //向上翻  
					break;
				case KEY_UP:	//控制LED0翻转  
					OLED_Clear(0);
					OLED_Refresh_Gram(0);	
					func_index=table[func_index].up;//向下翻
					break;
				case KEY_LEFT:	//控制LED1翻转	  
					if(func_index==3||func_index==4)//在调整界面按的确认
					{
						STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
						datatemp[0]=TEXT_Buffer[0];
						datatemp[1]=TEXT_Buffer[1];
					}
					if(func_index==1||func_index==2)//在选择界面按的确认
					{
						STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
						TEXT_Buffer[0]=datatemp[0];
						TEXT_Buffer[1]=datatemp[1];
					}
					OLED_Clear(0);
					OLED_Refresh_Gram(0);					
						func_index=table[func_index].enter;//回车
					break;
				case KEY_DOWN:	//同时控制LED0,LED1翻转 
					if(func_index==1)  datatemp[0]=TEXT_Buffer[0];//在选择界面按的减小
					if(func_index==2)  datatemp[1]=TEXT_Buffer[1];//在选择界面按的减小
					if(func_index==3)  TEXT_Buffer[0]-=100;//在调整界面按的减小
					if(func_index==4)  TEXT_Buffer[1]-=100;//在调整界面按的减小
					OLED_Clear(0);
					OLED_Refresh_Gram(0);	
					func_index=table[func_index].exit;//回车
					break;
		}
		}else delay_ms(10); 
		
	current_operation_index=table[func_index].current_operation;
	(*current_operation_index)();//执行当前操作函数
}

void  fun0(void)
{ 

	u8 j;
	u8 b;
	b=Flag_Margin;
	//显示是否危险
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
	//显示是否危险
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
	//显示是否危险
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
	//显示主界面1
	OLED_ShowChinese_num(0,16,4,0,0);
	OLED_Refresh_Gram(0);
}

void  fun2(void)
{
	//显示主界面2
	OLED_ShowChinese_num(0,16,4,1,0);
	OLED_Refresh_Gram(0);
}
void  fun3(void)
{
	//显示调整界面1
	
	OLED_ShowNum(93,48,TEXT_Buffer[0],4,16,0);//显示ASCII字符的码值 
	OLED_Refresh_Gram(0);	
}
void  fun4(void)
{
 //显示调整界面2
	OLED_ShowNum(93,48,TEXT_Buffer[1],4,16,0);//显示ASCII字符的码值 
	OLED_Refresh_Gram(0);
}





