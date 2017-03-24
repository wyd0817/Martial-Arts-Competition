#include "adc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"

#define ADC1_DR_Address 0x4001244c//ADC �������ݼĴ�����ַ



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
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
    
    ADC_DeInit(ADC1); //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
    
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ģ��ת�������ڶ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת������������ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 4;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
  
//		ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_239Cycles5);//����1·
//		ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_239Cycles5);//����2·
//		ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_239Cycles5);//����3·
//		ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_239Cycles5);//����4·
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_4,5,ADC_SampleTime_239Cycles5);//����5·
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_5,6,ADC_SampleTime_239Cycles5);//����6·
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_6,7,ADC_SampleTime_239Cycles5);//����7·
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_7,8,ADC_SampleTime_239Cycles5);//����8·


    ADC_RegularChannelConfig(ADC1,ADC_Channel_8,2,ADC_SampleTime_239Cycles5);//����9·
    ADC_RegularChannelConfig(ADC1,ADC_Channel_9,1,ADC_SampleTime_239Cycles5);//����10·
    ADC_RegularChannelConfig(ADC1,ADC_Channel_10,3,ADC_SampleTime_239Cycles5);//����11·
    ADC_RegularChannelConfig(ADC1,ADC_Channel_14,4,ADC_SampleTime_239Cycles5);//����13·



//	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_239Cycles5);//����9·
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_9,2,ADC_SampleTime_239Cycles5);//����10·
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_10,3,ADC_SampleTime_239Cycles5);//����11· 
//    ADC_RegularChannelConfig(ADC1,ADC_Channel_14,4,ADC_SampleTime_239Cycles5);//����13·  
//  ǰ��  AD0
//  ǰ��  AD1
//  ZUOHOU AD2
//  YOUHOU AD3
//  
//  PB0 PB1 PC0 PC4
    ADC_DMACmd(ADC1,ENABLE);
    
    ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
    ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
  
    ADC_ResetCalibration(ADC1); //����ADC1��У׼�Ĵ���
    while(ADC_GetResetCalibrationStatus(ADC1)); //��ȡADC1����У׼�Ĵ�����״̬
    ADC_StartCalibration(ADC1);  //��ʼУ׼ADC1
    while(ADC_GetCalibrationStatus(ADC1));   //�ȴ�У׼����
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); //ʹ��ָ����ADC1�����ת����������  

}




void Adc_Io_Init(void)
{
		//��ʼ��12���Ҷȴ�����
    GPIO_InitTypeDef GPIO_InitStructure;
    
//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
//    GPIO_Init(GPIOA, &GPIO_InitStructure);	
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
    GPIO_Init(GPIOC, &GPIO_InitStructure);	
}

void Adc_Dma(void)
{
    DMA_InitTypeDef DMA_InitStructure;//����DMA�ṹ��

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
    DMA_DeInit(DMA1_Channel1);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ

    DMA_InitStructure.DMA_PeripheralBaseAddr=ADC1_DR_Address;//ADC �������ݼĴ�����ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCvalue; //���ݴ洢��Ŀ���ַ
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//������Ϊ���ݴ������Դ
    DMA_InitStructure.DMA_BufferSize =4;  //DMAͨ����DMA����Ĵ�С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord ;  //�������ݿ��Ϊ16λ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //�ڴ����ݿ��Ϊ16λ
    DMA_InitStructure.DMA_Mode =DMA_Mode_Circular;  //������ѭ������ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ��1ӵ�и����ȼ�
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��1û������Ϊ�ڴ浽�ڴ洫��
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);//������洢���ʹ洢��֮��ķ���

    DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);//����DMA1ͨ��1��������ж�
    DMA_Cmd(DMA1_Channel1,ENABLE);
   
}














