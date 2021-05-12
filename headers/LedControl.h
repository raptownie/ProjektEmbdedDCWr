#ifndef LEDCONTROLHeader
#define LEDCONTROLHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include "Config.h"
#include "Typedef.h"
#include "UserSystemInit.h"

void DisplayShow (void);
void BlinkLed(void);
void AllLedsOff(void);
void InitStruct_LedsStatus_tab (void);
void AllLedsOn(void);
void SetLedOn(LedStatus_t *, uint8_t );
void SetLedOff(LedStatus_t *, uint8_t );
void SetLedBlinkOn(LedStatus_t *, uint8_t );
void SetLedBlinkOff(LedStatus_t *, uint8_t  );
void SetAllLedsBlinkOn(void);
void SetAllLedsBlinkOff(void);
void GoStandbyModeDeviceLedShow(void);
void DeviceAfterWakeUpLedShow(void);

#endif
