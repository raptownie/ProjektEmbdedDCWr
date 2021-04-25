#ifndef _Timers
#define _Timers

#ifndef _DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#ifndef _UserSystemInit
#include "../headers/UserSystemInit.h"
#endif

void TIM7_config(void);
void TIM7_IRQHandler(void);

#endif
