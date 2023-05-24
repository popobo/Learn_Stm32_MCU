#include "stm32f10x.h"

void PWM_Init(void)
{
    //初始化GPIOA_Pin0
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIOA_init_stru;
    GPIOA_init_stru.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出，让定时器进行输出控制
    GPIOA_init_stru.GPIO_Pin = GPIO_Pin_0;
    GPIOA_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOA_init_stru);

    GPIO_SetBits(GPIOA, GPIO_Pin_0);

    //时基单元初始化
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_InternalClockConfig(TIM2);
    
    TIM_TimeBaseInitTypeDef TIM_time_base_stru;
    TIM_time_base_stru.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_time_base_stru.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_time_base_stru.TIM_Period = 100 -1; // ARR
    TIM_time_base_stru.TIM_Prescaler = 720 - 1; // PSC
    TIM_time_base_stru.TIM_RepetitionCounter = 0; //高级定时器才有
    TIM_TimeBaseInit(TIM2, &TIM_time_base_stru);

    TIM_Cmd(TIM2, ENABLE);

    TIM_OCInitTypeDef TIM_oc_init_stru;
    TIM_OCStructInit(&TIM_oc_init_stru);
    TIM_oc_init_stru.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_oc_init_stru.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_oc_init_stru.TIM_OutputState = TIM_OutputState_Enable;
    TIM_oc_init_stru.TIM_Pulse = 0; // CCR
    TIM_OC1Init(TIM2, &TIM_oc_init_stru);
    
    TIM_Cmd(TIM2, ENABLE);
}

void Pwm_SetCompare1(uint16_t compare)
{
    TIM_SetCompare1(TIM2, compare);
}
