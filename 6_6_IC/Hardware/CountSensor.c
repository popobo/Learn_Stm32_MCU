#include "stm32f10x.h"
#include "CountSensor.h"

static CountSensor_Handler m_handler;

void CountSensor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_InitTypeDef GPIO_init_stru;
    GPIO_init_stru.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_init_stru.GPIO_Pin = GPIO_Pin_11;
    GPIO_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_init_stru);

    // B11 --> {AFIO} --> EXTI14 --> NVIC --> CPU
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);

    EXTI_InitTypeDef EXTI_init_stru;
    EXTI_init_stru.EXTI_Line = EXTI_Line11;
    EXTI_init_stru.EXTI_LineCmd = ENABLE;
    EXTI_init_stru.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_init_stru.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_init_stru);

    //分组方式整个芯片只能用同一种
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_init_stru;
    NVIC_init_stru.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_init_stru.NVIC_IRQChannelCmd = ENABLE;
    NVIC_init_stru.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_init_stru.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_init_stru);
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line11) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 1)
        { 
            m_handler();
        }
        EXTI_ClearITPendingBit(EXTI_Line11);
    }
}

void CountSensor_Set_Handler(CountSensor_Handler handler)
{
    m_handler = handler;
}
