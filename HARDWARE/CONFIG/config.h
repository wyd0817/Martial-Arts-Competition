#ifndef __CONFIG_H
#define __CONFIG_H 	 


//#define SER_AD_VALUE_12_MAIN
//#define SER_AD_VALUE_12 1  //�Ƿ���12����������ֵ
//#define SER_DANGER      1  //Σ��ʱ�Ƿ�ͨ�����ڷ���
//#define SER_DANGER_T      1  //Σ��ʱ�Ƿ�ͨ�����ڷ���


#define CRUISE_SPEED  200  //�ڱ�Եʱ�ĸ��ٷ�Χ��0-1000(ֵԽ���ٶ�Խ��)

//#define HIGH_SPEED 450  //�ڱ�Եʱ�ĵ��� ��Χ��0-1000(ֵԽ���ٶ�Խ��)
//#define LOW_SPEED  140  //�ڱ�Եʱ�ĸ��ٷ�Χ��0-1000(ֵԽ���ٶ�Խ��)
//#define SUPER_HIGH_SPEED 600  //�ڱ�Եʱ�ĵ��� ��Χ��0-1000(ֵԽ���ٶ�Խ��)

#define HIGH_SPEED 400  //�ڱ�Եʱ�ĵ��� ��Χ��0-1000(ֵԽ���ٶ�Խ��)
#define LOW_SPEED  240  //�ڱ�Եʱ�ĸ��ٷ�Χ��0-1000(ֵԽ���ٶ�Խ��)
#define SUPER_HIGH_SPEED 600  //�ڱ�Եʱ�ĵ��� ��Χ��0-1000(ֵԽ���ٶ�Խ��)

#define SUPER_HIGH_SPEED_1 400  //�ڱ�Եʱ�ĵ��� ��Χ��0-1000(ֵԽ���ٶ�Խ��)

//#define ROUND_HIGH_SPEED 340  //�ڱ�Եʱ�ĵ��� ��Χ��0-1000(ֵԽ���ٶ�Խ��)
//#define ROUND_LOW_SPEED  190  //�ڱ�Եʱ�ĸ��ٷ�Χ��0-1000(ֵԽ���ٶ�Խ��)
//#define ROUND_SUPER_HIGH_SPEED 400  //�ڱ�Եʱ�ĵ��� ��Χ��0-1000(ֵԽ���ٶ�Խ��)


#define ROUND_HIGH_SPEED 450  //�ڱ�Եʱ�ĵ��� ��Χ��0-1000(ֵԽ���ٶ�Խ��)
#define ROUND_LOW_SPEED  100  //�ڱ�Եʱ�ĸ��ٷ�Χ��0-1000(ֵԽ���ٶ�Խ��)
#define ROUND_SUPER_HIGH_SPEED 460  //�ڱ�Եʱ�ĵ��� ��Χ��0-1000(ֵԽ���ٶ�Խ��)

#define MARK_TIME_T 100   //ʱ��ΪMARK_TIME*20����
#define MARK_TIME 100   //ʱ��ΪMARK_TIME*20����
#define MARK_HIGH_SPEED 200  //�ڱ�Եʱ�ĵ��� ��Χ��0-1000(ֵԽ���ٶ�Խ��)
#define MARK_LOW_SPEED  100  //�ڱ�Եʱ�ĸ��ٷ�Χ��0-1000(ֵԽ���ٶ�Խ��)


#define DELAY_MARGIN 200  //�ڱ�Եʱ�ĺ���ʱ��
#define SENSOR_LEFT  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) //��ߴ�����
#define SENSOR_RIGHT GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) //�ұߴ�����


#define DELAY_MARGIN_CHESS 200  //�ڱ�Եʱ�ĺ���ʱ��
#define HIGH_SPEED_CHESS  300
#define ROUND_HIGH_SPEED_CHESS  450
#define ROUND_SUPER_HIGH_SPEED_CHESS  550
#define SUPER_HIGH_SPEED_CHESS 500  //�ڱ�Եʱ�ĵ��� ��Χ��0-1000(ֵԽ���ٶ�Խ��)




#endif
