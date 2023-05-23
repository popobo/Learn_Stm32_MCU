#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_init_stru;
    GPIO_init_stru.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_init_stru.GPIO_Pin = GPIO_Pin_0;
    GPIO_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_init_stru);
	//GPIO_ResetBits(GPIOA, GPIO_Pin_0);
    GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
    while(1)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
        Delay_ms(500);
        GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
        Delay_ms(500);
	}
}
