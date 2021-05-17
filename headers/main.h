#ifndef MAINHeader
#define MAINHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "GPIOInit.h"
#include "UserSystemInit.h"
#include "Timers.h"
#include "UART.h"
#include "SPI.h"
#include "Typedef.h"
#include "I2C.h"
#include "LedControl.h"
#include "MainPerform.h"

extern LedStatus_t tLedStatus[];
extern MainState_t MainState;
extern ButtonState_t ButtonState;

#endif
