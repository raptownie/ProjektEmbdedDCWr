#include "main.h"

 int main (void){
   
   /*** Clock Init ***/
   ClockConfig_HSE_with_PLL(); //72MHz
    
   /*** GPIOE LEDs Init (LD3-LD10); GPIOA Button PA0 Init ***/   
   GPIO_Init();
    
   /*** Sleep Mode config ***/
   StandbyConfig();   
   
   /*** Gyroskop config ***/
   SPI_Config_for_Gyroskop();
   
   /*** UART Init ***/
   UART4_Init_with_DMA_TIM1();
   
   /*** TurnOn All Timers ***/
   TurnOnTimers();
   
   while (PWR->CSR & PWR_CSR_SBF);     // czy po standby?
   
   while(1){
     // Gyroskop_L3GD20_XYZ_Read_Calculate();
      
      
      delay_ms(500);

      
      delay_ms(1000);
      GPIOE->ODR ^= 0xFF00;
      delay_ms(200);
      GPIOE->ODR ^= 0xFF00;
      delay_ms(300);
      GPIOE->ODR ^= 0xFF00;
      
      
   }
}
 

