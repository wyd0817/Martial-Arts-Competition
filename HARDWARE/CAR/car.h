#ifndef __CAR_H
#define __CAR_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/4
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//********************************************************************************


void TIM5_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void Car_Forward(u16 speed);
void Car_Back(u16 speed);
void Car_Pause(void);
void Car_Left_Forward(u16 speed);
void Car_Right_Forward(u16 speed);
void Car_Left_Back(u16 speed);
void Car_Right_Back(u16 speed);

void Car_Left_Forward_Chess(u16 speed);
void Car_Right_Forward_Chess(u16 speed);
void Car_Left_Back_Chess(u16 speed);
void Car_Right_Back_Chess(u16 speed);

void Car_Rotation(void);
void Car_Rotation_1(void);//单轮子打转低速
void Car_Rotation_2(void);//单轮子打转低速
#endif
