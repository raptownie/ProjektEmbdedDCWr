#ifndef TIMERSHeader
#define TIMERSHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include "UserSystemInit.h"
#include "Config.h"
#include "UART.h"
#include "SPI.h"
#include "Typedef.h"
#include "I2C.h"
#include "LedControl.h"
#include "ProjectPerform.h"
#include <string.h>

void TIM7_config(void);
void TIM7_IRQHandler(void);
void TIM1_config(void);
void TIM1_UP_TIM16_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM6_config(void);
void TIM6_DAC_IRQHandler(void);
void TurnOnTimers (void);
void TIM8_config(void);
void TIM8_UP_IRQHandler (void);

extern Mode_t ModeSelect;
extern DataToSendUART_t GyroskopXYZvalues;
extern DataToSendUART_t AcceleroXYZvalues;
extern uint8_t SizeOfDataToSendUART4;
extern uint8_t SizeOfDataToReciveUART4;

extern LedStatus_t tLedStatus[];

#endif
