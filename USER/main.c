/*
*********************************************************************************************************
*
*	模块名称 : 主程序模块。
*	文件名称 : main.c
*	版    本 : V1.0
*	说    明 : 
*             
*             
*	修改记录 :
*		版本号    日期       作者            说明
*		v1.0    2015-03-05  王永东     此程序是华北五省机器人擂台赛决赛程序
*
*	Copyright (C), 2014-2024, 草原神鹰工作组
*
*********************************************************************************************************
*/
#include "bsp_init.h"
#include "logic_qualifying.h"
#include "logic_elimination.h"

#define _SWTICH  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//模式按键

extern u8 Flag_Margin;//检测擂台台面的4个传感器(9-12)
extern u8 Flag_Enemy; //前后检测敌人的8个传感器(1-8)
extern u8 Flag_Size;  //侧面检测敌人的2个传感器(13-14)
extern delay_var delay_var_0,delay_var_1,delay_var_2,delay_var_3;
int main(void)
{

	bsp_Init();
//	while(1)
//	printf("左后1 左后2 右后2有敌人");
		
//		while(1)
//		{
//		delay_var_0.Allow_SoftTimer=1;
//	if(delay_var_0.SoftTimerCounter<10)	Car_Left_Forward(ROUND_LOW_SPEED);
//	else									Car_Pause();
//		}
	switch(_SWTICH)
	{
		case 0:Init_Qualifying(); break;//排位赛初始化（包括上台）
		case 1:Init_Elimination();break;//淘汰赛初始化（包括上台）
	}
	
	while(1)
	{
		if(_SWTICH==0)
		while(1)//排位赛程序
		{
			if((Flag_Enemy||Flag_Size)==0)//没有象棋
			{
				if(Flag_Margin==0)			Chess_0_Margin_0();//没有检测到边缘
				else if(Flag_Margin!=0)		Chess_0_Margin_1();//检测到边缘
			}
			else if((Flag_Enemy!=0)||(Flag_Size!=0))//遇见象棋
			{
				if(Flag_Margin==0)			Chess_1_Margin_0();//没有检测到边缘（撞象棋）	
				else if(Flag_Margin!=0)		Chess_1_Margin_1();//检测到边缘（特殊情况方法2装象棋）	
			}	
		}
		else if(_SWTICH==1)
		while(1)//淘汰赛程序
		{
			if((Flag_Enemy||Flag_Size)==0)//没有敌人
			{
				if(Flag_Margin==0)			Enemy_0_Margin_0();//没有检测到边缘
				else if(Flag_Margin!=0)		Enemy_0_Margin_1();//检测到边缘
			}
			else if((Flag_Enemy!=0)||(Flag_Size!=0))//遇见敌人
			{
				if(Flag_Margin==0)			Enemy_1_Margin_0();//没有检测到边缘（此种情况多数是检测到敌人，攻击模式）	
				else if(Flag_Margin!=0)		Enemy_1_Margin_1();//此种情况多数是被撞了，躲避模式
			}
		}
	}
}


/*
*********************************************************************************************************
															*测试电机函数*
//	Car_Forward(HIGH_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	Car_Forward(LOW_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	Car_Back(HIGH_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	Car_Back(LOW_SPEED);
//	delay_ms(1000);delay_ms(1000);
	
//	Car_Left_Forward(HIGH_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	Car_Right_Forward(HIGH_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	Car_Left_Back(HIGH_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	Car_Right_Back(HIGH_SPEED);
//	delay_ms(1000);delay_ms(1000);
//	
//	Car_Left_Forward_Chess(LOW_SPEED);
//	Car_Right_Forward_Chess(LOW_SPEED);
//	Car_Left_Back_Chess(LOW_SPEED);
//	Car_Right_Back_Chess(LOW_SPEED);

//	Car_Pause();
//	delay_ms(1000);delay_ms(1000);
//	while(1);

*********************************************************************************************************
*/




