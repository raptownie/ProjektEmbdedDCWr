#ifndef I2CHeader
#define I2CHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include "Typedef.h"
#include "Config.h"
#include "UserSystemInit.h"

void I2C_LSM303DLHC_Init(void);
void I2C_Write(uint8_t , uint8_t , uint8_t , uint8_t );
uint8_t I2C_Read(uint8_t , uint8_t , uint8_t);
void Accelero_LSM303DLHC_XYZ_Read_Calculate(void);

extern DataToSendUART_t AcceleroXYZvalues;

#endif
