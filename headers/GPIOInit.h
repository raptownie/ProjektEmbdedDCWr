#ifndef GPIOINITHeader
#define GPIOINITHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include "UserSystemInit.h"
#include "ProjectPerform.h"

void EXTI0_IRQHandler(void);
void GPIO_Init(void);

#endif
