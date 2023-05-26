#include "stm32f10x.h"

void Led_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIOA_init_stru;
    GPIOA_init_stru.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIOA_init_stru.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIOA_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOA_init_stru);

    GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
}

void Led1_On(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}

void Led1_Off(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_0);
}

void Led1_Turn(void)
{
    if(!GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0))
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_0);
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);
    }
}

void Led2_On(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

void Led2_Off(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

void Led2_Turn(void)
{
    if(!GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1))
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_1);
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
    }
}