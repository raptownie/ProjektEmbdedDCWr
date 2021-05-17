#ifndef BUTTONPERFORMHeader
#define BUTTONPERFORMHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include <stdbool.h>

#include "Typedef.h"

extern volatile uint32_t timer_ms;

void ButtonPerform_ButtonStatePerform(void);
bool ButtonPerform_CheckButtonState (ButtonState_t );
bool ButtonPerform_ButtonIsPressed(void);
bool ButtonPerform_ButtonIsUnpressed (void);

#endif
