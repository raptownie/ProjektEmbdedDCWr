#ifndef SPIHeader
#define SPIHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include <stdio.h>
#include "UART.h"
#include "Timers.h"

#define L3GD20_Reg_XL 0x28
#define L3GD20_Reg_XH 0x29
#define L3GD20_Reg_YL 0x2A
#define L3GD20_Reg_YH 0x2B
#define L3GD20_Reg_ZL 0x2C
#define L3GD20_Reg_ZH 0x2D



void Write_SPI(uint8_t reg, uint8_t data);
uint8_t Read_SPI(uint8_t reg);

void SPI_Config_for_Gyroskop(void);
void Gyroskop_L3GD20_XYZ_Read_Calculate(void);
void L3GD20_Init(void);





#endif
