#ifndef PROJEKTPERFORMHeader
#define PROJEKTPERFORMHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include <stdbool.h>

#include "Typedef.h"
#include "Config.h"
#include "UserSystemInit.h"
#include "LedControl.h"

void MainStatePerform(void);
void ButtonStatePerform(void);
bool CheckMainState (MainState_t );

extern uint32_t HowLongButtonIsPressed;
extern volatile uint32_t timer_ms;
extern bool *pTurnOnLedSequenceFinishFlag;
extern bool *pTurnOffLedSequenceFinishFlag;

#endif
