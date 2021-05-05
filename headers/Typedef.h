#ifndef Typedef
#define Typedef

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

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

typedef enum {On = 1, Off = 0}OnOffLed_t;

typedef enum {True = 1, False = 0}bool_t;

typedef struct LedStatus{
   OnOffLed_t OnOffStatus;
   bool_t blink; 
}LedStatus_t;

typedef struct AllLedStatus {
   LedStatus_t LD3;
   LedStatus_t LD4;
   LedStatus_t LD5;
   LedStatus_t LD6;
   LedStatus_t LD7;
   LedStatus_t LD8;
   LedStatus_t LD9;
   LedStatus_t LD10;
}AllLedStatus_t;


#endif
