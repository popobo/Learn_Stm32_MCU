
#include "stm32f10x.h"
#include "Encoder.h"

void Encoder_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIOA_init_stru;
    GPIOA_init_stru.GPIO_Mode = GPIO_Mode_IPU; // 看外部模块默认输入是高还是低来决定上下拉
    GPIOA_init_stru.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIOA_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIOA_init_stru);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    
    TIM_TimeBaseInitTypeDef TIM_time_base_stru;
    TIM_time_base_stru.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_time_base_stru.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_time_base_stru.TIM_Period = UINT16_MAX - 1;
    TIM_time_base_stru.TIM_Prescaler = 1 - 1;
    TIM_time_base_stru.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_time_base_stru);
    
    
    TIM_ICInitTypeDef TIM_IC_init_stru;
    TIM_ICStructInit(&TIM_IC_init_stru);
    TIM_IC_init_stru.TIM_Channel = TIM_Channel_1;
    TIM_IC_init_stru.TIM_ICFilter = 0xF;
    TIM_IC_init_stru.TIM_ICPolarity = TIM_ICPolarity_Rising; //此时代表高低电平极性不反转
    TIM_PWMIConfig(TIM3, &TIM_IC_init_stru);

    TIM_ICStructInit(&TIM_IC_init_stru);
    TIM_IC_init_stru.TIM_Channel = TIM_Channel_2;
    TIM_IC_init_stru.TIM_ICFilter = 0xF;
    TIM_IC_init_stru.TIM_ICPolarity = TIM_ICPolarity_Rising; //此时代表高低电平极性不反转
    TIM_PWMIConfig(TIM3, &TIM_IC_init_stru);

    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    TIM_Cmd(TIM3, ENABLE);
}

int16_t Encoder_Get(void)
{
    int16_t temp = TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3, 0);
    return temp;
}
