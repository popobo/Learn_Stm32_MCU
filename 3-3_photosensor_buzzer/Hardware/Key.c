#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void Key_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIOB_init_stru;
    GPIOB_init_stru.GPIO_Mode = GPIO_Mode_IPU;
    GPIOB_init_stru.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8;
    GPIOB_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIOB_init_stru);
}

uint8_t Key(void)
{
    uint8_t key_num = 0;
    if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
    {
        Delay_ms(20);
        while(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))
        {
            Delay_ms(20);
            key_num = 1;
        }
    }
    if (!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))
    {
        Delay_ms(20);
        while(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))
        {
            Delay_ms(20);
            key_num = 2;
        }
    }
    return key_num;
}
 