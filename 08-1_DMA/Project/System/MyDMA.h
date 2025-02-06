#ifndef MYDMA_H
#define MYDMA_H
#include <stdint.h>

void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint16_t Size);
void MyDMA_Transfer(void);
#endif //MYDMA_H
