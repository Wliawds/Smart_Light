#ifndef __ADJUSTLIGHT_H
#define __ADJUSTLIGHT_H
#include "stm32f4xx_hal.h"

#define adjust_max 999
#define adjust_min 1

void AdjustLight_Init(void);
int AdjustLight(uint16_t adjustCount);

#endif
