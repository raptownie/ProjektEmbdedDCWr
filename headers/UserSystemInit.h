#ifndef _UserSystemInit
#define _UserSystemInit

#ifndef _DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#ifndef _Timers
#include "Timers.h"
#endif

void ClockConfig_HSE_with_PLL(void);
void SysTick_Handler(void);
void delay_ms(uint32_t time);
void StandbyConfig(void);
void GoSleep (void);

#endif
