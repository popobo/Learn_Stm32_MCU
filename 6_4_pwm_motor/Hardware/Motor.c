#include "stm32f10x.h"
#include "Pwm.h"

void Motor_Init()
{
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIOA_init_stru;
    GPIOA_init_stru.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIOA_init_stru.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIOA_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOA_init_stru);

    PWM_Init();
}


void Motor_SetSpeed(int8_t speed)
{
    if(speed >= 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        Pwm_SetCompare3(speed);
    }
    else
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);
        Pwm_SetCompare3(-speed);
    }
}
