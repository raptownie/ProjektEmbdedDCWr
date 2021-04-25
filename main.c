#ifndef _DeviceHeader
#define _DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#include "headers/GPIOInit.h"
#include "headers/UserSystemInit.h"
#include "headers/Timers.h"

int main (void){
   
   /*** Clock Init ***/
   ClockConfig_HSE_with_PLL(); //72MHz
    
   /*** GPIOE LEDs Init ***/
   GPIOE_LED_Init(); // LD3-10 init
   
   /*** GPIOA Button PA0 Init ***/
   GPIOA_BUTTON_Init();
   
   /*** Sleep Mode config ***/
   StandbyConfig();   
   
   /*** TIM7 ***/
   TIM7_config();  
   
   while (PWR->CSR & PWR_CSR_SBF);
   
   while(1){
      delay_ms(1000);
      GPIOE->ODR ^= 0xFF00;
      delay_ms(200);
      GPIOE->ODR ^= 0xFF00;
      delay_ms(300);
      GPIOE->ODR ^= 0xFF00;
      
      
   }
}
