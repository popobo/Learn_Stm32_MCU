#ifndef __MYDMA_H_
#define __MYDMA_H_

#include <stdint.h>

void MYDMA_Init(uint32_t addr_src, uint32_t addr_dst, uint16_t size);

void MYDMA_Transfer(uint16_t size);

#endif
