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
bool CheckButtonPressed(void);
void ChangeButtonState (ButtonState_t );
bool CheckButtonState (ButtonState_t );
void ChangeMainState (MainState_t );
bool CheckMainState (MainState_t );
bool ButtonIsPressedBy_ms (uint32_t );
void ClearStandbyFlag(void);
bool ButtonIsUnpressed (void);

extern uint32_t HowLongButtonIsPressed;
extern volatile uint32_t timer_ms;
extern bool *pTurnOnLedSequenceFinishFlag;
extern bool *pTurnOffLedSequenceFinishFlag;

#endif
