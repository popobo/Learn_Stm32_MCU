
#include "stm32f10x.h"
#include "Encoder.h"

static Encoder_Handler m_handler = 0;

void Encoder_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_InitTypeDef GPIO_init_stru;
    GPIO_init_stru.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_init_stru.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_init_stru);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

    EXTI_InitTypeDef EXTI_init_stru;
    EXTI_init_stru.EXTI_Line = EXTI_Line0 | EXTI_Line1;
    EXTI_init_stru.EXTI_LineCmd = ENABLE;
    EXTI_init_stru.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_init_stru.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_init_stru);

    //分组方式整个芯片只能用同一种
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_init_stru;
    NVIC_init_stru.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_init_stru.NVIC_IRQChannelCmd = ENABLE;
    NVIC_init_stru.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_init_stru.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_init_stru);

    NVIC_init_stru.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_init_stru.NVIC_IRQChannelCmd = ENABLE;
    NVIC_init_stru.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_init_stru.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_init_stru);
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0)
        {
            if (m_handler != 0) m_handler(1);
        }
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}


void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
        {
            if (m_handler != 0) m_handler(-1);
        }
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}


void Encoder_Set_Handler(Encoder_Handler handler)
{
    m_handler = handler;
}
