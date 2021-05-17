#ifndef USERSYSTEMINITHeader
#define USERSYSTEMINITHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include "Timers.h"
#include "GPIOInit.h"
#include <stdbool.h>

void SysTick_Handler(void);
void GoSleep (void);
void UserSystemInit_SystemSetup (void);

#endif
