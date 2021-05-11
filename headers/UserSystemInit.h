#ifndef USERSYSTEMINITHeader
#define USERSYSTEMINITHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include "Timers.h"
#include "GPIOInit.h"
#include <stdbool.h>

void ClockConfig_HSE_with_PLL(void);
void SysTick_Handler(void);
void delay_ms(uint32_t time);
void StandbyConfig(void);
void GoSleep (void);
void SystemSetup (void);

#endif
