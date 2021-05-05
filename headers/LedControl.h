#ifndef LedControl
#define LedControl

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include "Config.h"
#include "Typedef.h"

void DisplayShow (void);
void BlinkLed(void);
void AllLedsOff(void);
void InitStruct_LedsStatus_t (void);
void AllLedsOn(void);
void SetLedOn(LedStatus_t *);
void SetLedOff(LedStatus_t *);
void SetLedBlinkOn(LedStatus_t *);
void SetLedBlinkOff(LedStatus_t *);

#endif
