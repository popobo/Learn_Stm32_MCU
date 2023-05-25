#include "stm32f10x.h"
#include "IC.h"

void IC_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIOA_init_stru;
    GPIOA_init_stru.GPIO_Mode = GPIO_Mode_IPU;
    GPIOA_init_stru.GPIO_Pin = GPIO_Pin_6;
    GPIOA_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIOA_init_stru);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_InternalClockConfig(TIM3);
    
    TIM_TimeBaseInitTypeDef TIM_time_base_stru;
    TIM_time_base_stru.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_time_base_stru.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_time_base_stru.TIM_Period = UINT16_MAX -1;
    TIM_time_base_stru.TIM_Prescaler = 72 - 1;
    TIM_time_base_stru.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_time_base_stru);
    
    TIM_ICInitTypeDef TIM_IC_init_stru;
    TIM_IC_init_stru.TIM_Channel = TIM_Channel_1;
    TIM_IC_init_stru.TIM_ICFilter = 0xF;
    TIM_IC_init_stru.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_IC_init_stru.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_IC_init_stru.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM3, &TIM_IC_init_stru);

    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);

    TIM_Cmd(TIM3, ENABLE);
}

uint32_t IC_GetFreq(void)
{
    return 1000000 / TIM_GetCapture1(TIM3);
}
