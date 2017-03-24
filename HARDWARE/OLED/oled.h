#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	    
//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0
		    						  
//-----------------OLED端口定义----------------  					   

#define OLED_CS0_Clr()  GPIO_ResetBits(GPIOC,GPIO_Pin_6)	//PC6·CS0： Chip Selection
#define OLED_CS0_Set()  GPIO_SetBits(GPIOC,GPIO_Pin_6)

#define OLED_CS1_Clr()  GPIO_ResetBits(GPIOC,GPIO_Pin_7)	//PC7·CS1： Chip Selection
#define OLED_CS1_Set()  GPIO_SetBits(GPIOC,GPIO_Pin_7)

#define OLED_CS2_Clr()  ;
#define OLED_CS2_Set()  ;

#define OLED_RST_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_3)   //PC3·RST： RESET
#define OLED_RST_Set() GPIO_SetBits(GPIOC,GPIO_Pin_3)

#define OLED_RS_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_5)   //PC5·DC:data or cmd
#define OLED_RS_Set() GPIO_SetBits(GPIOC,GPIO_Pin_5)

//#define OLED_WR_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_2)
//#define OLED_WR_Set() GPIO_SetBits(GPIOC,GPIO_Pin_2)

//#define OLED_RD_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_1)
//#define OLED_RD_Set() GPIO_SetBits(GPIOC,GPIO_Pin_1)
	

//PC0~7,作为数据线
#define DATAOUT(x) GPIO_Write(GPIOC,x);//输出  
//使用4线串行接口时使用 

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_6)//D0
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_6)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_1)//D1
#define OLED_SDIN_Set() GPIO_SetBits(GPIOC,GPIO_Pin_1)

 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd,u8 cs);	    
void OLED_Display_On(u8 cs);
void OLED_Display_Off(u8 cs);
void OLED_Refresh_Gram(u8 cs);		   

void OLED_IO_Init(void);
void OLED_Init(u8 cs);
void OLED_Clear(u8 cs);
void OLED_DrawPoint(u8 x,u8 y,u8 t,u8 cs);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot,u8 cs);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode,u8 cs);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size,u8 cs);
void OLED_ShowString(u8 x,u8 y,u8 *p,u8 cs);	
void OLED_ShowChinese_num(u8 x,u8 y,u8 num,u8 mode,u8 cs);
#endif  


