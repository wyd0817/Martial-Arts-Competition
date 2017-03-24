/*
*********************************************************************************************************
*
*	模块名称 : LOGIC_ELIMINATION模块(For STM32F1XX)
*	文件名称 : logic_elimination.c
*	版    本 : V1.0
*	说    明 : 这是程序逻辑的主文件。每个c文件可以 #include "logic.h" 来包含所有的外设驱动模块。
*			   logic_elimination 逻辑 淘汰赛
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2013-03-01  CYSY   正式发布
*
*	Copyright (C), 2014-2024, 草原神鹰工作组
*
*********************************************************************************************************
*/

#include "logic_elimination.h"
#include "bsp_init.h"
	
	

/************************************定义全局变量****************************************/
	u32 k=0;
	u8 Flag_Safety=1;
	extern u8 Flag_Forward;
	extern u32 Enemy_Count[10];
	extern u32 Table_Count[4];
	extern u8 Flag_Margin;//检测擂台台面的4个传感器(9-12)
	extern u8 Flag_Enemy; //前后检测敌人的8个传感器(1-8)
	extern u8 Flag_Size;  //侧面检测敌人的2个传感器(13-14)
	extern u16 Margin_Critcal;
	extern u16 Enemy_Critical;
	extern u16 TEXT_Buffer[2];
	extern u16 datatemp[SIZE];
	extern __IO uint16_t ADCvalue[4];
	extern delay_var delay_var_0,delay_var_1,delay_var_2,delay_var_3;


void Init_Elimination(void)
{
	/******************  (￣▽￣)~ ********* (⊙?⊙) ********* <(￣︶￣)>   ******************/
	
	//STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
	OLED_ShowChinese_num(0,16,4,1,0);
	OLED_Refresh_Gram(0);
	

	//STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
	TEXT_Buffer[0]=datatemp[0];
	TEXT_Buffer[1]=datatemp[1];
	while(RIGH_ENEMY_Y==0)
	{
		//Menu_key_set();
		//printf("value_0=%4d  value_1=%4d\r\n",datatemp[0],datatemp[1]);
	}
	while(RIGH_ENEMY_Y!=0);
	Enemy_Critical=datatemp[0];
	Margin_Critcal=datatemp[1];
	//printf("Enemy_Critical=%4d  Margin_Critcal=%4d\r\n",Enemy_Critical,Margin_Critcal);
	
	/***********************************上台函数******************************************/
	Car_Forward(300);
	delay_ms(1100);
	Car_Forward(950);
	delay_ms(200);
	Car_Right_Forward(297);
	delay_ms(200);
	Car_Forward(CRUISE_SPEED);

	/******************  (￣▽￣)~ ********* (⊙?⊙) ********* <(￣︶￣)>   ******************/
}

void Enemy_1_Margin_0(void)
{	
	/**********************四个传感器检测到敌人**********************/
		if(LEFT_FRONT_1&&LEFT_FRONT_2&&RIGH_FRONT_1&&RIGH_FRONT_2)//左前1 左前2 右前2 右前1
		{
			printf("左前1 左前2 右前2 右前1有敌人");
			printf("\r\n\r\n");
			Car_Forward(LOW_SPEED);
		}
		else if(LEFT_FRONT_1&&LEFT_FRONT_2&&RIGH_FRONT_1&&RIGH_FRONT_2)//左后1 左后2 右后2 右后1
		{
			printf("左后1 左后2 右后2 右后1有敌人");
			printf("\r\n\r\n");
			Car_Back(LOW_SPEED);
		}
		/******************  (￣▽￣)~ ********* (⊙?⊙) ********* <(￣︶￣)>   ******************/
		
		/**********************三个传感器检测到敌人/**********************/
		
		else if(LEFT_FRONT_1&&LEFT_FRONT_2&&RIGH_FRONT_2&&(RIGH_FRONT_1==0))//左前1 左前2 右前2
		{
			printf("左前1 左前2 右前2有敌人");
			printf("\r\n\r\n");
			Car_Forward(SUPER_HIGH_SPEED);
		}
		else if(RIGH_FRONT_2&&LEFT_FRONT_2&&RIGH_FRONT_1&&(LEFT_FRONT_1==0))//左前2 右前2 右前1
		{
			printf("左前2 右前2 右前1有敌人");
			printf("\r\n\r\n");
			Car_Forward(SUPER_HIGH_SPEED);
		}
		else if(LEFT_AFTER_1&&LEFT_AFTER_2&&RIGH_AFTER_2&&(RIGH_AFTER_1==0))//左后1 左后2 右后2
		{
			printf("左后1 左后2 右后2有敌人");
			printf("\r\n\r\n");
			Car_Back(SUPER_HIGH_SPEED);
		}
		else if(LEFT_AFTER_2&&RIGH_AFTER_2&&RIGH_AFTER_1&&(LEFT_AFTER_1==0))//左后2 右后2 右后1
		{
			printf("左后2 右后2 右后1有敌人");
			printf("\r\n\r\n");
			Car_Back(SUPER_HIGH_SPEED);
		}
		
		else if(LEFT_FRONT_1&&LEFT_ENEMY_Y&&LEFT_FRONT_1)//左前1 左侧 左后1
		{
			printf("左前1 左侧 左后1有敌人");
			printf("\r\n\r\n");
			for (k = 0; k < 8; k++)
			{
				if(LEFT_FRONT_1||LEFT_FRONT_2||RIGH_FRONT_2||RIGH_FRONT_1)
				{
					break;
				}
				printf("前面左侧有敌人");
				printf("\r\n\r\n");
				Car_Left_Forward(ROUND_SUPER_HIGH_SPEED);
				delay_ms(2);
			}			
			Car_Left_Forward(ROUND_SUPER_HIGH_SPEED);
		}
		else if(RIGH_AFTER_1&&RIGH_ENEMY_Y&&RIGH_FRONT_1)//右后1 右侧 右后1
		{
			printf("//右前1 右侧 右后1有敌人");
			printf("\r\n\r\n");
					for (k = 0; k < 8; k++)
			{
				if(LEFT_FRONT_1||LEFT_FRONT_2||RIGH_FRONT_2||RIGH_FRONT_1)
				{
					break;
				}
				printf("前面左侧有敌人");
				printf("\r\n\r\n");
				Car_Right_Back(ROUND_SUPER_HIGH_SPEED);
				delay_ms(2);
			}	
		}
		/******************  (￣▽￣)~ ********* (⊙?⊙) ********* <(￣︶￣)>   ******************/
		
		/**********************两个传感器检测到敌人/**********************/
		
		else if(RIGH_FRONT_2&&LEFT_FRONT_2&&(RIGH_FRONT_1==0)&&(LEFT_FRONT_1==0))//左前2 右前2
		{
			printf("左前2 右前2有敌人");
			printf("\r\n\r\n");
			Car_Forward(SUPER_HIGH_SPEED);
		}		
		else if(LEFT_FRONT_1&&LEFT_FRONT_2&&(RIGH_FRONT_1==0)&&(RIGH_FRONT_2==0))//左前1 左前2
		{
			printf("左前1 左前2有敌人");
			printf("\r\n\r\n");
			Car_Forward(HIGH_SPEED);
		}
		else if(RIGH_FRONT_1&&RIGH_FRONT_2&&(LEFT_FRONT_1==0)&&(LEFT_FRONT_2==0))//右前1 右前2
		{
			printf("右前1 右前2有敌人");
			printf("\r\n\r\n");
			Car_Forward(HIGH_SPEED);
		}
	
		else if(RIGH_AFTER_2&&LEFT_AFTER_2&&(RIGH_AFTER_1==0)&&(LEFT_AFTER_1==0))//左后2 右后2
		{
			printf("/左后2 右后2有敌人");
			printf("\r\n\r\n");
			Car_Back(SUPER_HIGH_SPEED);
		}
		
		else if(LEFT_AFTER_1&&LEFT_AFTER_2&&(RIGH_AFTER_1==0)&&(RIGH_AFTER_2==0))//左后1 左后2
		{
			printf("左后1 左后2有敌人");
			printf("\r\n\r\n");
			Car_Back(HIGH_SPEED);
		}
		else if(RIGH_AFTER_1&&RIGH_AFTER_2&&(LEFT_AFTER_1==0)&&(LEFT_AFTER_2==0))//右后1 右后2
		{
			printf("右后1 右后2有敌人");
			printf("\r\n\r\n");
			Car_Back(HIGH_SPEED);
		}
	
		else if(LEFT_FRONT_1&&LEFT_ENEMY_Y&&(LEFT_AFTER_1==0))//左前1 左侧
		{
			printf("左前1 左侧有敌人");
			printf("\r\n\r\n");
			/* 等待RIGH_FRONT_2&&LEFT_FRONT_2 (超时200ms) */
			for (k = 0; k < 8; k++)
			{
				if(LEFT_FRONT_1||LEFT_FRONT_2||RIGH_FRONT_2||RIGH_FRONT_1)
				{
					break;
				}
				printf("前面左侧有敌人");
				printf("\r\n\r\n");
				Car_Left_Forward(ROUND_SUPER_HIGH_SPEED);
				delay_ms(2);
			}		
		}
		else if(LEFT_AFTER_1&&LEFT_ENEMY_Y&&(LEFT_FRONT_1==0))//左后1 左侧
		{
			printf("左后1 左侧有敌人");
			printf("\r\n\r\n");
			/* 等待RIGH_FRONT_2&&LEFT_FRONT_2 (超时200ms) */
			for (k = 0; k < 8; k++)
			{
				if(LEFT_FRONT_1||LEFT_FRONT_2||RIGH_FRONT_2||RIGH_FRONT_1)
				{
					break;
				}
				printf("前面左侧有敌人");
				printf("\r\n\r\n");
				Car_Left_Back(ROUND_SUPER_HIGH_SPEED);
				delay_ms(2);
			}		
		}
		else if(RIGH_FRONT_1&&RIGH_ENEMY_Y&&(RIGH_AFTER_1==0))//右前1 右侧
		{
			printf("右前1 右侧有敌人");
			printf("\r\n\r\n");
			for (k = 0; k < 8; k++)
			{
				if(LEFT_FRONT_1||LEFT_FRONT_2||RIGH_FRONT_2||RIGH_FRONT_1)
				{
					break;
				}
				printf("前面左侧有敌人");
				printf("\r\n\r\n");
				Car_Right_Forward(ROUND_SUPER_HIGH_SPEED);
				delay_ms(2);
			}		
		}
		else if(RIGH_AFTER_1&&RIGH_ENEMY_Y&&(RIGH_FRONT_1==0))//右后1 右侧
		{
			printf("右后1 右侧有敌人");
			printf("\r\n\r\n");
			for (k = 0; k < 8; k++)
			{
				if(LEFT_FRONT_1||LEFT_FRONT_2||RIGH_FRONT_2||RIGH_FRONT_1)
				{
					break;
				}
				printf("前面左侧有敌人");
				printf("\r\n\r\n");
				Car_Right_Back(ROUND_SUPER_HIGH_SPEED);
				delay_ms(2);
			}			
		}
		/******************  (￣▽￣)~ ********* (⊙?⊙) ********* <(￣︶￣)>   ******************/
		
		
	
		/**********************单个传感器检测到敌人/**********************/
		 else if((LEFT_FRONT_2!=0)&&(LEFT_FRONT_1==0)&&(RIGH_FRONT_1==0)&&(RIGH_FRONT_2==0))//左前2
		{
				printf("左前2有敌人");
				printf("\r\n\r\n");
				Car_Forward(HIGH_SPEED);
		}
		
		else if((LEFT_FRONT_2==0)&&(LEFT_FRONT_1==0)&&(RIGH_FRONT_1==0)&&(RIGH_FRONT_2!=0))//右前2
		{
				printf("右前2有敌人");
				printf("\r\n\r\n");
				Car_Forward(HIGH_SPEED);
		}
		
		else if((LEFT_AFTER_2!=0)&&(LEFT_AFTER_1==0)&&(RIGH_AFTER_1==0)&&(RIGH_AFTER_2==0))//左后2
		{
				printf("左后2有敌人");
				printf("\r\n\r\n");
				Car_Back(HIGH_SPEED);
		}
		
		else if((LEFT_AFTER_2==0)&&(LEFT_AFTER_1==0)&&(RIGH_AFTER_1==0)&&(RIGH_AFTER_2!=0))//右后2
		{
				printf("右后2有敌人");
				printf("\r\n\r\n");
				Car_Back(HIGH_SPEED);
		}
		else if((LEFT_FRONT_2==0)&&(LEFT_FRONT_1!=0)&&(RIGH_FRONT_1==0)&&(RIGH_FRONT_2==0)&&(LEFT_ENEMY_Y==0)&&(LEFT_AFTER_1==0))//左前1
		{
			printf("左前1有敌人");
			printf("\r\n\r\n");
			delay_var_0.Allow_SoftTimer=1;
			if(delay_var_0.SoftTimerCounter<10)	Car_Left_Forward(ROUND_HIGH_SPEED);
			else									Car_Forward(HIGH_SPEED);						
				
		}
		else if((LEFT_FRONT_2==0)&&(LEFT_FRONT_1==0)&&(RIGH_FRONT_1!=0)&&(RIGH_FRONT_2==0)&&(RIGH_ENEMY_Y==0)&&(RIGH_AFTER_1==0))//右前1
		{
			printf("右前1有敌人");
			printf("\r\n\r\n");
			delay_var_1.Allow_SoftTimer=1;
			if(delay_var_1.SoftTimerCounter<10)	Car_Right_Forward(ROUND_HIGH_SPEED);
			else 									Car_Forward(HIGH_SPEED);
				
				
		}
		
		else if((LEFT_AFTER_2==0)&&(LEFT_AFTER_1!=0)&&(RIGH_AFTER_1==0)&&(RIGH_AFTER_2==0)&&(LEFT_ENEMY_Y==0)&&(LEFT_FRONT_1==0))//左后1
		{
				printf("左后1有敌人");
				printf("\r\n\r\n");
			delay_var_2.Allow_SoftTimer=1;
			if(delay_var_2.SoftTimerCounter<10)	Car_Left_Back(ROUND_HIGH_SPEED);
			else 									Car_Back(HIGH_SPEED);
				
				
		}
		else if((LEFT_AFTER_2==0)&&(LEFT_AFTER_1==0)&&(RIGH_AFTER_1!=0)&&(RIGH_AFTER_2==0)&&(RIGH_ENEMY_Y==0)&&(RIGH_FRONT_1==0))//右后1
		{
				printf("右后1有敌人");
				printf("\r\n\r\n");
				delay_var_3.Allow_SoftTimer=1;
				if(delay_var_3.SoftTimerCounter<10)	Car_Right_Back(ROUND_HIGH_SPEED);
				else									Car_Back(HIGH_SPEED);
		}
		
		else if((LEFT_ENEMY_Y!=0)&&(LEFT_FRONT_1==0)&&(LEFT_AFTER_1==0))//左侧
		{
				printf("//左侧有敌人");
				printf("\r\n\r\n");
								
					/* 等待RIGH_FRONT_2&&LEFT_FRONT_2 (超时200ms) */
					for (k = 0; k < 8; k++)
					{
						if(LEFT_FRONT_1||LEFT_FRONT_2||RIGH_FRONT_2||RIGH_FRONT_1)
						{
							break;
						}
						printf("前面左侧有敌人");
						printf("\r\n\r\n");
						Car_Left_Forward(ROUND_SUPER_HIGH_SPEED);
						delay_ms(2);
					}		
		}
		else if((RIGH_ENEMY_Y!=0)&&(RIGH_FRONT_1==0)&&(RIGH_AFTER_1==0))//右侧
		{
				printf("//右侧有敌人");
				printf("\r\n\r\n");
				/* 等待RIGH_FRONT_2&&LEFT_FRONT_2 (超时200ms) */
					for (k = 0; k < 8; k++)
					{
						if(LEFT_FRONT_1||LEFT_FRONT_2||RIGH_FRONT_2||RIGH_FRONT_1)
						{
							break;
						}
						printf("前面左侧有敌人");
						printf("\r\n\r\n");
						Car_Right_Back(ROUND_SUPER_HIGH_SPEED);
						delay_ms(2);
					}		
		}
		
		

		/******************  (￣▽￣)~ ********* (⊙?⊙) ********* <(￣︶￣)>   ******************/
		
	Flag_Safety=0;
}
void Enemy_0_Margin_1(void)
{
//	if(LEFT_AFTER_T&&RIGH_AFTER_T&&RIGH_FRONT_T&&LEFT_FRONT_T)
//	{
//		Car_Left_Forward_Chess(ROUND_LOW_SPEED);delay_ms(200);
//		if((ADCvalue[0]+ADCvalue[1])>(ADCvalue[0]+ADCvalue[1]))
//									Car_Forward(CRUISE_SPEED);
//		else
//									Car_Back(CRUISE_SPEED);
//	}
	if(LEFT_AFTER_T&&RIGH_AFTER_T)	
	{
		if(LEFT_FRONT_1&&LEFT_FRONT_2&&RIGH_FRONT_1&&RIGH_FRONT_2)
		Car_Forward(SUPER_HIGH_SPEED);delay_ms(100);
		Car_Left_Forward(ROUND_HIGH_SPEED);delay_ms(100);Car_Forward(CRUISE_SPEED);
	}//后面两个传感器都检测出台
	if(RIGH_FRONT_T&&LEFT_FRONT_T)	
	{
			Car_Back(SUPER_HIGH_SPEED);   delay_ms(100);
			Car_Right_Back(ROUND_HIGH_SPEED);delay_ms(100);Car_Back(CRUISE_SPEED);
	}//前面两个传感器都检测出台
	if(LEFT_AFTER_T&&(RIGH_AFTER_T==0))	 
	{
		Car_Forward(SUPER_HIGH_SPEED);delay_ms(100);
		Car_Left_Forward(ROUND_HIGH_SPEED);delay_ms(100);Car_Forward(CRUISE_SPEED);
		//OLED_ShowString(0,0,"AAAAAAA",1);OLED_Refresh_Gram(1);/*Car_Pause();while(1);*/
	}//9
	if(RIGH_AFTER_T&&(LEFT_AFTER_T==0))	 
	{
		Car_Forward(SUPER_HIGH_SPEED);delay_ms(100);
		Car_Left_Forward(ROUND_HIGH_SPEED);delay_ms(100);Car_Forward(CRUISE_SPEED);
		//OLED_ShowString(0,0,"BBBBBBB",1);OLED_Refresh_Gram(1);/*CCar_Pause();while(1);*/
	}//10
	if(LEFT_FRONT_T&&(RIGH_FRONT_T==0))	 
	{
		Car_Back(SUPER_HIGH_SPEED);delay_ms(100);
		Car_Right_Back(ROUND_HIGH_SPEED);delay_ms(100);Car_Back(CRUISE_SPEED);
		//OLED_ShowString(0,0,"CCCCCCCC",1);OLED_Refresh_Gram(1);/*CCar_Pause();while(1);*/
	}//11
	if(RIGH_FRONT_T&&(LEFT_FRONT_T==0))	 
	{
		Car_Back(SUPER_HIGH_SPEED);delay_ms(100);
		Car_Right_Back(ROUND_HIGH_SPEED);delay_ms(100);Car_Back(CRUISE_SPEED);
		//OLED_ShowString(0,0,"DDDDDDDD",1);OLED_Refresh_Gram(1);/*CCar_Pause();while(1);*/
	}//12

}
void Enemy_0_Margin_0(void)
{
	if(Flag_Safety==0)	
	{
//		if((Table_Count[0]>0)&&(Table_Count[1]>0)&&(Table_Count[2]>0)&&(Table_Count[3]>0))
//		{
//			if(Enemy_Count[0]>0)		Car_Left_Forward(MARK_HIGH_SPEED);
//			else if(Enemy_Count[1]>0)	Car_Left_Forward(MARK_LOW_SPEED);
//			else if(Enemy_Count[2]>0)	Car_Right_Forward(MARK_LOW_SPEED);
//			else if(Enemy_Count[3]>0)	Car_Right_Forward(MARK_HIGH_SPEED);
//			else if(Enemy_Count[4]>0)	Car_Right_Back(MARK_HIGH_SPEED);
//			else if(Enemy_Count[5]>0)	Car_Right_Back(MARK_LOW_SPEED);
//			else if(Enemy_Count[6]>0)	Car_Left_Back(MARK_LOW_SPEED);
//			else if(Enemy_Count[7]>0)	Car_Left_Back(MARK_HIGH_SPEED);
//			else if(Enemy_Count[8]>0)	Car_Right_Forward_Chess(MARK_HIGH_SPEED);
//			else if(Enemy_Count[9]>0)	Car_Right_Forward_Chess(MARK_HIGH_SPEED);
//			else 
//			{
//				if(Flag_Forward==1)			Car_Forward(CRUISE_SPEED);//不处理
//				else if(Flag_Forward==0)	Car_Back(CRUISE_SPEED);//不处理
//				Flag_Safety=1;
//			}
//		}
//		else
//		{
			if(Flag_Forward==1)			Car_Forward(CRUISE_SPEED);//不处理
			else if(Flag_Forward==0)	Car_Back(CRUISE_SPEED);//不处理
			Flag_Safety=1;
//		}
	}
}
void Enemy_1_Margin_1(void)
{
	if(LEFT_AFTER_T&&RIGH_AFTER_T&&RIGH_FRONT_T&&LEFT_FRONT_T)
	{
		Car_Left_Forward_Chess(ROUND_LOW_SPEED);delay_ms(200);
		if((ADCvalue[0]+ADCvalue[1])>(ADCvalue[0]+ADCvalue[1]))
									Car_Forward(CRUISE_SPEED);
		else
									Car_Back(CRUISE_SPEED);
	}
	
	else if(LEFT_AFTER_T&&RIGH_AFTER_T)	
	{
		if((LEFT_FRONT_1==1)||(RIGH_FRONT_1==1)||(LEFT_AFTER_1==1)||(RIGH_AFTER_1==1)||(RIGH_ENEMY_Y==1)||(LEFT_ENEMY_Y==1))
		{
		/*Car_Pause();delay_ms(100);*/Car_Forward(SUPER_HIGH_SPEED);delay_ms(DELAY_MARGIN);
		Car_Left_Forward(ROUND_HIGH_SPEED);delay_ms(200);Car_Forward(LOW_SPEED);
//			printf("\r\n\r\n");
//			printf("WANGYONGQngyong");
//			printf("\r\n\r\n");
//			Car_Pause();
//			while(1);
		}
		else if((RIGH_AFTER_2==1)||(LEFT_AFTER_2==1))
		{
			Car_Pause();
//						printf("\r\n\r\n");
//			printf("cysysaydyasy");
//			printf("\r\n\r\n");
//			while(1);
			Car_Left_Forward(SUPER_HIGH_SPEED_1);delay_ms(1000);Car_Forward(LOW_SPEED);
		}
	}//后面两个传感器都检测出台
	else if(RIGH_FRONT_T&&LEFT_FRONT_T)	
	{
		if((LEFT_FRONT_1==1)||(RIGH_FRONT_1==1)||(LEFT_AFTER_1==1)||(RIGH_AFTER_1==1)||(RIGH_ENEMY_Y==1)||(LEFT_ENEMY_Y==1))
		{
			/*Car_Pause();delay_ms(100);*/Car_Back(SUPER_HIGH_SPEED);   delay_ms(DELAY_MARGIN);
			Car_Right_Back(ROUND_HIGH_SPEED);delay_ms(1000);Car_Back(LOW_SPEED);
		}
		else if((RIGH_FRONT_2==1)||(LEFT_FRONT_2==1))
		{
			Car_Pause();
			while(1);
			Car_Right_Back(SUPER_HIGH_SPEED_1);delay_ms(200);Car_Back(LOW_SPEED);
		}
	}//前面两个传感器都检测出台
	else if(LEFT_AFTER_T&&(RIGH_AFTER_T==0))	 
	{
		/*Car_Pause();delay_ms(100);*/Car_Forward(SUPER_HIGH_SPEED);delay_ms(DELAY_MARGIN);
	}//9
	else if(RIGH_AFTER_T&&(LEFT_AFTER_T==0))	 
	{
		/*Car_Pause();delay_ms(100);*/Car_Forward(SUPER_HIGH_SPEED);delay_ms(DELAY_MARGIN);
	}//10
	else if(LEFT_FRONT_T&&(RIGH_FRONT_T==0))	 
	{
		/*Car_Pause();delay_ms(100);*/Car_Back(SUPER_HIGH_SPEED);delay_ms(DELAY_MARGIN);
	}//11
	else if(RIGH_FRONT_T&&(LEFT_FRONT_T==0))	 
	{
		/*Car_Pause();delay_ms(100);*/Car_Back(SUPER_HIGH_SPEED);delay_ms(DELAY_MARGIN);
	}//12

}
	
/***************************** 草原神鹰工作组 CYSY (END OF FILE) *********************************/
