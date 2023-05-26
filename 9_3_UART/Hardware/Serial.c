#include "stm32f10x.h"

void Serial_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_init_stru;
    GPIO_init_stru.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_init_stru.GPIO_Pin = GPIO_Pin_9;
    GPIO_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_init_stru);

    USART_InitTypeDef USART_init_stru;

    USART_init_stru.USART_BaudRate = 9600;
    USART_init_stru.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_init_stru.USART_Mode = USART_Mode_Tx;
    USART_init_stru.USART_Parity = USART_Parity_No;
    USART_init_stru.USART_StopBits = USART_StopBits_1;
    USART_init_stru.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_init_stru);

    USART_Cmd(USART1, ENABLE);
}

void Serial_SenByte(uint8_t byte)
{
    USART_SendData(USART1, byte);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
    // 硬件清零
}
