#ifndef __CONFIG_H
#define __CONFIG_H 	 


//#define SER_AD_VALUE_12_MAIN
//#define SER_AD_VALUE_12 1  //是否发送12个传感器的值
//#define SER_DANGER      1  //危险时是否通过串口发送
//#define SER_DANGER_T      1  //危险时是否通过串口发送


#define CRUISE_SPEED  200  //在边缘时的高速范围：0-1000(值越大，速度越快)

//#define HIGH_SPEED 450  //在边缘时的低速 范围：0-1000(值越大，速度越快)
//#define LOW_SPEED  140  //在边缘时的高速范围：0-1000(值越大，速度越快)
//#define SUPER_HIGH_SPEED 600  //在边缘时的低速 范围：0-1000(值越大，速度越快)

#define HIGH_SPEED 400  //在边缘时的低速 范围：0-1000(值越大，速度越快)
#define LOW_SPEED  240  //在边缘时的高速范围：0-1000(值越大，速度越快)
#define SUPER_HIGH_SPEED 600  //在边缘时的低速 范围：0-1000(值越大，速度越快)

#define SUPER_HIGH_SPEED_1 400  //在边缘时的低速 范围：0-1000(值越大，速度越快)

//#define ROUND_HIGH_SPEED 340  //在边缘时的低速 范围：0-1000(值越大，速度越快)
//#define ROUND_LOW_SPEED  190  //在边缘时的高速范围：0-1000(值越大，速度越快)
//#define ROUND_SUPER_HIGH_SPEED 400  //在边缘时的低速 范围：0-1000(值越大，速度越快)


#define ROUND_HIGH_SPEED 450  //在边缘时的低速 范围：0-1000(值越大，速度越快)
#define ROUND_LOW_SPEED  100  //在边缘时的高速范围：0-1000(值越大，速度越快)
#define ROUND_SUPER_HIGH_SPEED 460  //在边缘时的低速 范围：0-1000(值越大，速度越快)

#define MARK_TIME_T 100   //时间为MARK_TIME*20毫秒
#define MARK_TIME 100   //时间为MARK_TIME*20毫秒
#define MARK_HIGH_SPEED 200  //在边缘时的低速 范围：0-1000(值越大，速度越快)
#define MARK_LOW_SPEED  100  //在边缘时的高速范围：0-1000(值越大，速度越快)


#define DELAY_MARGIN 200  //在边缘时的后退时间
#define SENSOR_LEFT  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) //左边传感器
#define SENSOR_RIGHT GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) //右边传感器


#define DELAY_MARGIN_CHESS 200  //在边缘时的后退时间
#define HIGH_SPEED_CHESS  300
#define ROUND_HIGH_SPEED_CHESS  450
#define ROUND_SUPER_HIGH_SPEED_CHESS  550
#define SUPER_HIGH_SPEED_CHESS 500  //在边缘时的低速 范围：0-1000(值越大，速度越快)




#endif
