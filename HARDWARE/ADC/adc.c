#include "adc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"

#define ADC1_DR_Address 0x4001244c//ADC 规则数据寄存器地址



__IO uint16_t ADCvalue[4]={0};



void Enemy_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}


void Adc_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure; 
	
    Adc_Io_Init();
    Adc_Dma();
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1|RCC_APB2Periph_ADC2,ENABLE);
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
    
    ADC_DeInit(ADC1); //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值
    
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在多通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//模数转换工作在连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 4;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
  
//		ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_239Cycles5);//设置1路
//		ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_239Cycles5);//设置2路
//		ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_239Cycles5);//设置3路
//		ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_239Cycles5);//设置4路
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_4,5,ADC_SampleTime_239Cycles5);//设置5路
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_5,6,ADC_SampleTime_239Cycles5);//设置6路
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_6,7,ADC_SampleTime_239Cycles5);//设置7路
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_7,8,ADC_SampleTime_239Cycles5);//设置8路


    ADC_RegularChannelConfig(ADC1,ADC_Channel_8,2,ADC_SampleTime_239Cycles5);//设置9路
    ADC_RegularChannelConfig(ADC1,ADC_Channel_9,1,ADC_SampleTime_239Cycles5);//设置10路
    ADC_RegularChannelConfig(ADC1,ADC_Channel_10,3,ADC_SampleTime_239Cycles5);//设置11路
    ADC_RegularChannelConfig(ADC1,ADC_Channel_14,4,ADC_SampleTime_239Cycles5);//设置13路



//	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_239Cycles5);//设置9路
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_9,2,ADC_SampleTime_239Cycles5);//设置10路
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_10,3,ADC_SampleTime_239Cycles5);//设置11路 
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_14,4,ADC_SampleTime_239Cycles5);//设置13路  
//  前作  AD0
//  前有  AD1
//  ZUOHOU AD2
//  YOUHOU AD3
//  
//  PB0 PB1 PC0 PC4
    ADC_DMACmd(ADC1,ENABLE);
    
    ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
    ADC_ResetCalibration(ADC1);	//使能复位校准  
  
    ADC_ResetCalibration(ADC1); //重置ADC1的校准寄存器
    while(ADC_GetResetCalibrationStatus(ADC1)); //获取ADC1重置校准寄存器的状态
    ADC_StartCalibration(ADC1);  //开始校准ADC1
    while(ADC_GetCalibrationStatus(ADC1));   //等待校准结束
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); //使能指定的ADC1的软件转换启动功能  

}




void Adc_Io_Init(void)
{
		//初始化12个灰度传感器
    GPIO_InitTypeDef GPIO_InitStructure;
    
//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
//    GPIO_Init(GPIOA, &GPIO_InitStructure);	
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
    GPIO_Init(GPIOC, &GPIO_InitStructure);	
}

void Adc_Dma(void)
{
    DMA_InitTypeDef DMA_InitStructure;//定义DMA结构体

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
    DMA_DeInit(DMA1_Channel1);   //将DMA的通道1寄存器重设为缺省值

    DMA_InitStructure.DMA_PeripheralBaseAddr=ADC1_DR_Address;//ADC 规则数据寄存器地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCvalue; //数据存储的目标地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//外设作为数据传输的来源
    DMA_InitStructure.DMA_BufferSize =4;  //DMA通道的DMA缓存的大小
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord ;  //外设数据宽度为16位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //内存数据宽度为16位
    DMA_InitStructure.DMA_Mode =DMA_Mode_Circular;  //工作在循环缓存模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道1拥有高优先级
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道1没有设置为内存到内存传输
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);//不允许存储器和存储器之间的访问

    DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);//配置DMA1通道1传输完成中断
    DMA_Cmd(DMA1_Channel1,ENABLE);
   
}














