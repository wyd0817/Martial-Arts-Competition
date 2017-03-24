#include "beep.h"

//初始化PC9为输出口.并使能这个口的时钟		    
//蜂鸣器初始化
void BEEP_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能GPIOC端口时钟
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //BEEP-->PC.9 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);	 //根据参数初始化GPIOC.9
 
 GPIO_ResetBits(GPIOC,GPIO_Pin_9);//输出0，关闭蜂鸣器输出

}
