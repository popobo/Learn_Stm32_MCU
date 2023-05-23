#ifndef __ENCODER_H_
#define __ENCODER_H_

#include <stdint.h>

typedef void(*Encoder_Handler)(int8_t value);

void Encoder_Init(void);

void Encoder_Set_Handler(Encoder_Handler handler);

#endif
