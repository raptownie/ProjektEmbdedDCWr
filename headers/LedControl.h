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

void DisplayShow (LedStatus_t *);
void BlinkLed(LedStatus_t *);
void AllLedsOff(LedStatus_t *);
void InitStruct_LedsStatus_tab (LedStatus_t *);
void AllLedsOn(LedStatus_t *);
void SetLedOn(LedStatus_t *, uint8_t );
void SetLedOff(LedStatus_t *, uint8_t );
void SetLedBlinkOn(LedStatus_t *, uint8_t );
void SetLedBlinkOff(LedStatus_t *, uint8_t  );
void SetAllLedsBlinkOn(LedStatus_t *);
void SetAllLedsBlinkOff(LedStatus_t *);

extern volatile uint32_t timer_ms;
extern bool *pTurnOnLedSequenceStartFlag;
extern bool *pTurnOffLedSequenceStartFlag;
#endif
