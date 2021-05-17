#ifndef UARTHeader
#define UARTHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include "Typedef.h"
#include "Timers.h"

void UART_UART4_Init_with_DMA_TIM1(void);
void UART_Send_Gyro_Date_XYZ_UART(void);
void UART_Send_Data_Gyro_Accelero_XYZ_UART(void);
void UART_DMAHandleUART (void);

#endif
