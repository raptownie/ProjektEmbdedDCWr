#include "headers/main.h"

 int main (void){
   
   /*** Clock Init ***/
   ClockConfig_HSE_with_PLL(); //72MHz
    
   /*** GPIOE LEDs Init (LD3-LD10); GPIOA Button PA0 Init ***/   
   GPIO_Init();
       
   /*** Sleep Mode config ***/
   StandbyConfig();   
       
   /*** Gyroskop config ***/
   SPI_Config_for_Gyroskop();
    
    /*** Accelero config ***/
   I2C_LSM303DLHC_Init();
   
   /*** UART Init ***/
   UART4_Init_with_DMA_TIM1();
    
   /** ShowDisplay Init ***/
   InitStruct_LedsStatus_t();
   TIM8_config();
   
   /*** TurnOn All Timers ***/
   TurnOnTimers();
   
  
   
   while (PWR->CSR & PWR_CSR_SBF);     // czy po standby?
  
   
   while(1){
     // SetLedBlinkOn(&(tLedStatus[1]));
      /*
      delay_ms(1000);
      GPIOE->ODR ^= 0xFE00;
      delay_ms(1000);
      GPIOE->ODR ^= 0xFE00;
      delay_ms(1000);
      GPIOE->ODR ^= 0xFE00;
      */
      
   }
}
 

