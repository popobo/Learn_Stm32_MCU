#include "stm32f10x.h"

uint16_t AD_value[4];

void AD_Init(void)
{    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //外设时钟初始化必须放到操作外设之前
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    //初始化ADC
    ADC_InitTypeDef ADC_init_stru;
    ADC_StructInit(&ADC_init_stru);
    ADC_init_stru.ADC_Mode = ADC_Mode_Independent;
    ADC_init_stru.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_init_stru.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_init_stru.ADC_NbrOfChannel = sizeof(AD_value)/sizeof(AD_value[0]);
    ADC_init_stru.ADC_ContinuousConvMode = DISABLE;
    ADC_init_stru.ADC_ScanConvMode = ENABLE;
    ADC_Init(ADC1, &ADC_init_stru);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);

    //中断和看门狗
    //...

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_value;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = sizeof(AD_value)/sizeof(AD_value[0]);
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    DMA_Cmd(DMA1_Channel1, ENABLE);
    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    //校准
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1) == SET);
}


void AD_GetValue(void)
{
    DMA_Cmd(DMA1_Channel1, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel1, sizeof(AD_value)/sizeof(AD_value[0]));
    DMA_Cmd(DMA1_Channel1, ENABLE);

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    // while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); 转运总是在转换之后
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);
}
