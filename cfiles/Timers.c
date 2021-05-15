#include "../headers/Timers.h"


uint32_t HowLongButtonIsPressed = 0;

/*** TIM7 wykorzystuje do wlaczania i wylaczania urzadzenia ***/
void TIM7_config(void){
   RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;                // podlaczenie zegara pod TIM7
   TIM7->PSC = TIM7_Prescaler;                                // dzielnik ustawiony na 10000 - 72Mhz/10000 = 7200 impulsow na 1s
   TIM7->ARR = TIM7_AutoReloadRegisterValue;                                  // Przerwanie zakladam co 0,1s a wiec co 720 impulsow 
   TIM7->DIER |= TIM_DIER_UIE;                                 // Update interrupt enabled
   NVIC_SetPriority(TIM7_IRQn,5);   
   NVIC_EnableIRQ(TIM7_IRQn);
}

void TIM7_IRQHandler(void){   
   if (TIM7->SR & TIM_CR1_CEN){               
      if ((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0) {
         HowLongButtonIsPressed++;        
      }else HowLongButtonIsPressed = 0;             
      TIM7->SR &= ~TIM_SR_UIF;                        // clearowanie flagi przerwania  
   }
}   

/*** TIM1 wykorzystuje do UARTa ***/

void TIM1_config(void){   
   RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;                // zegar taktowany 72MHz - bez dzielnika
   TIM1->PSC = TIM1_Prescaler;                        // Ustawienie prescalera timera 72MHz/TIM1_Prescaler = x impulsów na 1s
   TIM1->ARR = TIM1_AutoReloadRegisterValue;          // Ustawienie przerwania licznika glównego - co ile impulsów
   TIM1->DIER |= TIM_DIER_UIE;                        // Update interrupt enabled
   NVIC_SetPriority(TIM1_UP_TIM16_IRQn,3);            // Ustawienie priorytetu licznika TIM1
   NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);                // Wlaczenie przerwania
   
   //config kanalu CCR1 - send uart
   TIM1->CCR1 = TIM1_CCR1_value;
   TIM1->DIER |= TIM_DIER_CC1IE;
   
   NVIC_SetPriority(TIM1_CC_IRQn,4);                  // ustawienie priorytetu kanalow licznika TIM1
   NVIC_EnableIRQ(TIM1_CC_IRQn); 
   
   //TIM1->CR1 |= TIM_CR1_CEN;                          // Wlaczenie licznika TIM1
}

void TIM1_UP_TIM16_IRQHandler(void){   
   if(((TIM1->SR) & TIM_SR_UIF) == TIM_SR_UIF){      
      BlinkLed(LedStructName);      
      DMAHandleUART();      
      TIM1->SR &= ~TIM_SR_UIF;                        // Czyszczenie flagi glownego przerwania TIM1 
   } 
}

void TIM1_CC_IRQHandler(void){
   if(((TIM1->SR) & TIM_SR_CC1IF) == TIM_SR_CC1IF){            // sprawdzenie czy przerwanie wywolujace funkcje pochodzi od CC1
      Send_Data_Gyro_Accelero_XYZ_UART();
      TIM1-> SR &= ~TIM_SR_CC1IF;                     // Czyszczenie flagi przerwania od CC1
   }
}

//To Read Data from Gyro and Accelero
void TIM6_config(void){
   RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;                // podlaczenie zegara pod TIM7
   TIM6->PSC = TIM6_Prescaler;                                // dzielnik ustawiony na 10000 - 72Mhz/10000 = 7200 impulsow na 1s
   TIM6->ARR = TIM6_AutoReloadRegisterValue;                                  // Przerwanie zakladam co 0,1s a wiec co 720 impulsow 
   TIM6->DIER |= TIM_DIER_UIE;                                 // Update interrupt enabled
   NVIC_SetPriority(TIM6_DAC_IRQn,5);   
   NVIC_EnableIRQ(TIM6_DAC_IRQn);

}

void TIM6_DAC_IRQHandler(void){
   if(((TIM6->SR) & TIM_SR_UIF) == TIM_SR_UIF){
      if (CheckMainState(GyroState)) 
         Gyroskop_L3GD20_XYZ_Read_Calculate();
      else if (CheckMainState(AcceleroState))
         Accelero_LSM303DLHC_XYZ_Read_Calculate();
      TIM6->SR &= ~TIM_SR_UIF;
   }
}

void TIM8_config(void){
   RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;                // zegar taktowany 72MHz - bez dzielnika
   TIM8->PSC = TIM8_Prescaler;                        // Ustawienie prescalera timera 72MHz/TIM1_Prescaler = x impulsów na 1s
   TIM8->ARR = TIM8_AutoReloadRegisterValue;          // Ustawienie przerwania licznika glównego - co ile impulsów
   TIM8->DIER |= TIM_DIER_UIE;                        // Update interrupt enabled
   NVIC_SetPriority(TIM8_UP_IRQn,1);            // Ustawienie priorytetu licznika TIM1
   NVIC_EnableIRQ(TIM8_UP_IRQn);                // Wlaczenie przerwania

}


void TurnOnTimers (void){
   TIM1->CR1 |= TIM_CR1_CEN;                          // Wlaczenie licznika TIM1
   TIM6->CR1 |= TIM_CR1_CEN;                          // Wlaczenie licznika TIM6
   TIM7->CR1 |= TIM_CR1_CEN;                          // Wlaczenie licznika TIM7
   TIM8->CR1 |= TIM_CR1_CEN;                         // Wlaczenie licznika TIM8
}


  
void TIM8_UP_IRQHandler (void){
     if(((TIM8->SR) & TIM_SR_UIF) == TIM_SR_UIF){      
      DisplayShow(LedStructName);      
      TIM8->SR &= ~TIM_SR_UIF;
   }
}
   

