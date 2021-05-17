#ifndef LEDCONTROLHeader
#define LEDCONTROLHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include <stdbool.h>
#include "Config.h"
#include "Typedef.h"
#include "UserSystemInit.h"

void LedControl_DisplayShow (LedStatus_t *);
void LedControl_BlinkLed(LedStatus_t *);
void LedControl_AllLedsOff(LedStatus_t *);
void LedControl_InitStruct_LedsStatus_tab (LedStatus_t *);
void LedControl_AllLedsOn(LedStatus_t *);
void LedControl_SetLedOn(LedStatus_t *, uint8_t );
void LedControl_SetLedOff(LedStatus_t *, uint8_t );
void LedControl_SetLedBlinkOn(LedStatus_t *, uint8_t );
void LedControl_SetLedBlinkOff(LedStatus_t *, uint8_t  );
void LedControl_SetAllLedsBlinkOn(LedStatus_t *);
void LedControl_SetAllLedsBlinkOff(LedStatus_t *);
bool LedControl_SequenceLedGoToStandbyDone (void);
bool LedControl_SequenceLedAfterWakeUpDone (void);

extern volatile uint32_t timer_ms;

#endif
