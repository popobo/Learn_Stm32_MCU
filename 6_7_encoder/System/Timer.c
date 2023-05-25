#include "stm32f10x.h"
#include "Timer.h"

static Timer_Handler m_handler = 0;

void Timer_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    TIM_InternalClockConfig(TIM2);
    TIM_TimeBaseInitTypeDef TIM_time_base_stru;
    TIM_time_base_stru.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_time_base_stru.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_time_base_stru.TIM_Period =  10000 - 1;
    TIM_time_base_stru.TIM_Prescaler = 7200 - 1;
    TIM_time_base_stru.TIM_RepetitionCounter = 0; //高级定时器才有
    /*
    Generate an update event to reload the Prescaler and the Repetition counter values immediately
    TIMx->EGR = TIM_PSCReloadMode_Immediate;
    TIM_TimeBaseInit会触发一次中断
    */
    TIM_TimeBaseInit(TIM2, &TIM_time_base_stru);

    TIM_ClearFlag(TIM2, TIM_IT_Update);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_init_stru;
    NVIC_init_stru.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_init_stru.NVIC_IRQChannelCmd = ENABLE;
    NVIC_init_stru.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_init_stru.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_init_stru);

    TIM_Cmd(TIM2, ENABLE);
}


// void TIM2_IRQHandler(void)
// {
//     if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//     {
//         if (m_handler != 0) m_handler();
//         TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//     }
// }

void Timer_Set_Handler(Timer_Handler handler)
{
    m_handler = handler;
}

uint16_t Timer_GetCounter(void)
{
    return TIM_GetCounter(TIM2);
}
