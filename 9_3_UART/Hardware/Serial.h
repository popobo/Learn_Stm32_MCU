#ifndef __SERIAL_H_
#define __SERIAL_H_

#include <stdint.h>

#define SERIAL_PACK_ST 0xFF
#define SERIAL_PACK_ED 0xFE
#define SERIAL_PACK_LEN 4

extern uint8_t Serial_tx_packet[SERIAL_PACK_LEN];
extern uint8_t Serial_rx_packet[SERIAL_PACK_LEN];

void Serial_Init(void);

void Serial_SenByte(uint8_t byte);

void Serial_SendArray(uint8_t* array, uint16_t length);

void Serial_SendString(const char* string);

void Serial_SendNumber(uint32_t number, uint8_t len);

void Serial_printf(char* format, ...);

uint8_t Serial_GetRxFlag(void);

void Serial_SendPacket(void);

#endif
