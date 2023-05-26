#include "stm32f10x.h"

void MYDMA_Init(uint32_t addr_src, uint32_t addr_dst, uint16_t size)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    DMA_InitTypeDef DMA_init_stru;
    DMA_StructInit(&DMA_init_stru);
    DMA_init_stru.DMA_PeripheralBaseAddr = addr_src;
    DMA_init_stru.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_init_stru.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_init_stru.DMA_MemoryBaseAddr = addr_dst;
    DMA_init_stru.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_init_stru.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_init_stru.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_init_stru.DMA_BufferSize = size;
    DMA_init_stru.DMA_Mode = DMA_Mode_Normal;
    DMA_init_stru.DMA_M2M = DMA_M2M_Enable;
    DMA_init_stru.DMA_Priority = DMA_Priority_Medium;
    DMA_Init(DMA1_Channel1, &DMA_init_stru);

}



void MYDMA_Transfer(uint16_t size)
{
    DMA_Cmd(DMA1_Channel1, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel1, size);
    DMA_Cmd(DMA1_Channel1, ENABLE);
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);
}
