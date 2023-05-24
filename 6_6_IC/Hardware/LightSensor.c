#include "stm32f10x.h"

void LightSensor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitTypeDef GPIO_init_stru;
    GPIO_init_stru.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_init_stru.GPIO_Pin = GPIO_Pin_13;
    GPIO_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_init_stru);
}

uint8_t LightSensor_Is_On(void)
{
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}
