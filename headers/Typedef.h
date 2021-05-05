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

#endif
