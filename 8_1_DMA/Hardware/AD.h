#ifndef __AD_H_
#define __AD_H_

#include <stdint.h>

void AD_Init(void);

uint16_t AD_GetValue(uint8_t ADC_channel);

#endif
