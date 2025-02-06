#ifndef STORE_H
#define STORE_H
#include <stdint.h>

extern uint16_t Store_Data[512];
void Store_Init(void);

void Store_Save(void);

void Store_Clear(void);

#endif //STORE_H
