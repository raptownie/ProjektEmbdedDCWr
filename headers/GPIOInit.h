#ifndef _GPIOINIT
#define _GPIOINIT

#ifndef _DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#ifndef _UserSystemInit
#include "UserSystemInit.h"
#endif

void GPIOE_LED_Init(void);
void GPIOA_BUTTON_Init(void);
void EXTI0_IRQHandler(void);
/*
typedef enum RCC_GPIO
{
   GPIO_A = RCC_AHBENR_GPIOAEN,
   GPIO_B = RCC_AHBENR_GPIOBEN,
   GPIO_C = RCC_AHBENR_GPIOCEN,
   GPIO_D = RCC_AHBENR_GPIODEN,
   GPIO_E = RCC_AHBENR_GPIOEEN,
   GPIO_F = RCC_AHBENR_GPIOFEN      
} RCC_GPIOx_t;

typedef enum GPIOx_Moder
{
   GPIO_Moder_Input = 0x0,
   GPIO_Moder_Output = 0x1,
   GPIO_Moder_AF = 0x2,
   GPIO_Moder_Analog = 0x3   
}GPIOx_Moder_t;
 
void GPIOx_Init(RCC_GPIOx_t GPIO_x, GPIOx_Moder_t GPIO_Moder);

*/
  
#endif
