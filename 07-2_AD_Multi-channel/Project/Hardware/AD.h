#ifndef AD_H
#define AD_H
#include <stdint.h>

void AD_Init(void);
uint16_t AD_GetValue(uint8_t ADC_Channel);
#endif //AD_H
