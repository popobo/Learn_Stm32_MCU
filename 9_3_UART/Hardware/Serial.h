#ifndef __SERIAL_H_
#define __SERIAL_H_

#include <stdint.h>

void Serial_Init(void);

void Serial_SenByte(uint8_t byte);

void Serial_SendArray(uint8_t* array, uint16_t length);

void Serial_SendString(const char* string);

void Serial_SendNumber(uint32_t number, uint8_t len);

void Serial_printf(char* format, ...);

#endif
