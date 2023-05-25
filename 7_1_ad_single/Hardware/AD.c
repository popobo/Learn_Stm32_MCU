#include "stm32f10x.h"

void AD_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIOA_init_stru;
    GPIOA_init_stru.GPIO_Mode = GPIO_Mode_AIN;
    GPIOA_init_stru.GPIO_Pin = GPIO_Pin_0;
    GPIOA_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIOA_init_stru);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); //配置ADC时钟 

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_28Cycles5); //配置ADC通道
    
    //初始化ADC
    ADC_InitTypeDef ADC_init_stru;
    ADC_StructInit(&ADC_init_stru);
    ADC_init_stru.ADC_Mode = ADC_Mode_Independent;
    ADC_init_stru.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_init_stru.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_init_stru.ADC_NbrOfChannel = 1;
    ADC_init_stru.ADC_ContinuousConvMode = DISABLE;
    ADC_init_stru.ADC_ScanConvMode = DISABLE;
    ADC_Init(ADC1, &ADC_init_stru);

    //中断和看门狗
    //...

    ADC_Cmd(ADC1, ENABLE);

    //校准
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t AD_GetValue(void)
{
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}
