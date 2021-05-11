#ifndef TYPEDEFHeader
#define TYPEDEFHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include <stdbool.h>

typedef struct Gyroskop_Accelero_values {
   int16_t X_value;
   int16_t Y_value;
   int16_t Z_value;
}sGyro_Acce_XYZ_t;

typedef enum Mode {
   Accelero = 0, 
   Gyro = 1
} Mode_t;

typedef struct DataToSendUARTGyroAccelero {
   sGyro_Acce_XYZ_t values;
   uint16_t thresholdX;
   uint16_t thresholdY;
   uint16_t thresholdZ;
}DataToSendUART_t;

typedef enum {
   On = 1, 
   Off = 0
}OnOffLed_t;



typedef enum {
   LD3_ODR_BIT = GPIO_ODR_9,
   LD4_ODR_BIT = GPIO_ODR_8,
   LD5_ODR_BIT = GPIO_ODR_10,
   LD6_ODR_BIT = GPIO_ODR_15,
   LD7_ODR_BIT = GPIO_ODR_11,
   LD8_ODR_BIT = GPIO_ODR_14,
   LD9_ODR_BIT = GPIO_ODR_12,
   LD10_ODR_BIT = GPIO_ODR_13    
}LedPin_ODR_BIT_t;


typedef struct LedStatus{
   LedPin_ODR_BIT_t Pin_ODR;
   OnOffLed_t OnOffStatus;
   bool blink; 
}LedStatus_t;

typedef enum {
   GyroState = 0, 
   AcceleroState = 1, 
   GoStandbyState = 2, 
   AfterWakeUpState = 3
} MainState_t;

typedef enum {
   JustPressed = 0,
   Unpressed = 1,
   ButtonPressedLongerToGoStandby = 3
} ButtonState_t;


#endif
