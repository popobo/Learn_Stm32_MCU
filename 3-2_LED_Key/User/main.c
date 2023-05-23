#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIOA_init_stru;
    GPIOA_init_stru.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIOA_init_stru.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIOA_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOA_init_stru);

    GPIO_InitTypeDef GPIOB_init_stru;
    GPIOB_init_stru.GPIO_Mode = GPIO_Mode_IPU;
    GPIOB_init_stru.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
    GPIOB_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIOB_init_stru);

    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);

    while(1)
	{
        
	}
}
