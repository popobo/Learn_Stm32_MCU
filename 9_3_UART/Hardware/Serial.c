#include "stm32f10x.h"
#include <stdarg.h>
#include <stdio.h>

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
