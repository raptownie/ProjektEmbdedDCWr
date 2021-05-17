#ifndef PROJEKTPERFORMHeader
#define PROJEKTPERFORMHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include <stdbool.h>

#include "ButtonPerform.h"
#include "Typedef.h"
#include "Config.h"
#include "UserSystemInit.h"
#include "LedControl.h"

void MainPerform_MainStatePerform(void);
bool MainPerform_CheckMainState (MainState_t );

#endif
