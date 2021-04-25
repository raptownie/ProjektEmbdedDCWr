#include "../headers/Timers.h"


void TIM7_config(void){
   RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;                // podlaczenie zegara pod TIM7
   TIM7->PSC = 10000-1;                                // dzielnik ustawiony na 10000 - 72Mhz/10000 = 7200 impulsow na 1s
   TIM7->ARR = 720;                                  // Przerwanie zakladam co 0,1s a wiec co 720 impulsow 
   TIM7->DIER |= TIM_DIER_UIE;                                 // Update interrupt enabled
   NVIC_SetPriority(TIM7_IRQn,1);   
   NVIC_EnableIRQ(TIM7_IRQn);
   TIM7->CR1 |= TIM_CR1_CEN;
}

void TIM7_IRQHandler(void){   
   static uint16_t StandbyCounter=0;
   if (TIM7->SR & TIM_CR1_CEN){
      if (!(PWR->CSR & PWR_CSR_SBF)){         
         if ((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0) {
            if((StandbyCounter++)>30) GoSleep();         
         }else StandbyCounter=0; 
      }else{
         if ((GPIOA->IDR & GPIO_IDR_0) == GPIO_IDR_0) {
            if((StandbyCounter++)>30){
               PWR->CR |= PWR_CR_CSBF;
               StandbyCounter=0;
            }                        
         }else GoSleep();  
      }          
      
         
      TIM7->SR &= ~TIM_CR1_CEN;                        // clearowanie flagi przerwania  
   }
}   
