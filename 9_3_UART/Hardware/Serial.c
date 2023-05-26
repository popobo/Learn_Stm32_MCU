#include "stm32f10x.h"
#include <stdarg.h>
#include <stdio.h>

uint8_t serial_rx_data;
uint8_t serial_rx_flag;

void Serial_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_init_stru;
    GPIO_init_stru.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_init_stru.GPIO_Pin = GPIO_Pin_9;
    GPIO_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_init_stru);

    GPIO_init_stru.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_init_stru.GPIO_Pin = GPIO_Pin_10;
    GPIO_init_stru.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_init_stru);

    USART_InitTypeDef USART_init_stru;

    USART_init_stru.USART_BaudRate = 9600;
    USART_init_stru.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_init_stru.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_init_stru.USART_Parity = USART_Parity_No;
    USART_init_stru.USART_StopBits = USART_StopBits_1;
    USART_init_stru.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_init_stru);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_init_stru;
    NVIC_init_stru.NVIC_IRQChannel = USART1_IRQn;
    NVIC_init_stru.NVIC_IRQChannelCmd = ENABLE;
    NVIC_init_stru.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_init_stru.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_init_stru);

    USART_Cmd(USART1, ENABLE);
}

void Serial_SenByte(uint8_t byte)
{
    USART_SendData(USART1, byte);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
    // 硬件清零
}

void Serial_SendArray(uint8_t* array, uint16_t length)
{
    for(uint16_t i = 0; i < length; ++i)
    {
        Serial_SenByte(array[i]);
    }
}


void Serial_SendString(const char* string)
{
    for(uint16_t i = 0; string[i] != '\0'; ++i)
    {
        Serial_SenByte(string[i]);
    }
}

static uint32_t Serial_Pow(uint32_t x, uint32_t y)
{
    uint32_t result = 1;
    while(y--)
    {
        result *= x;
    }
    return result;
}

void Serial_SendNumber(uint32_t number, uint8_t len)
{
    uint8_t i;
    for(i = 0; i < len; i++)
    {
        Serial_SenByte(number / Serial_Pow(10, len - i - 1) % 10 + '0');
    }
}

void Serial_printf(char* format, ...)
{
    char string[128];
    va_list arg;
    va_start(arg, format);
    vsprintf(string, format, arg);
    va_end(arg);
    Serial_SendString(string);
}

uint8_t Serial_GetRxFlag(void)
{
    if(serial_rx_flag == 1)
    {
        serial_rx_flag = 0;
        return 1;
    }
    return 0;
}

uint8_t Serial_GetRxData(void)
{
    return serial_rx_data;
}

void USART1_IRQHandler(void)
{
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
    {
        serial_rx_data = USART_ReceiveData(USART1);
        serial_rx_flag = 1;
        USART_ClearITPendingBit(USART1, USART_FLAG_RXNE);
    }
}
