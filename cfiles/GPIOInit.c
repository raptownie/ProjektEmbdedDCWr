#include "../headers/GPIOInit.h"


 /*** GPIOE LEDs Init LD3-10***/
static void GPIOE_LED_Init(void){
   // Enabled clock for GPIOE
   RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
   
   /*** config PE8-15 as pushpull output for LEDS ***/
   //Set as OUTPUT (MODER 01)
   GPIOE->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 
                  | GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0 | GPIO_MODER_MODER13_0 
                  | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;
   GPIOE->MODER &=  (~GPIO_MODER_MODER8_1 | ~GPIO_MODER_MODER9_1 | ~GPIO_MODER_MODER10_1 
                  | ~GPIO_MODER_MODER11_1 | ~GPIO_MODER_MODER12_1 | ~GPIO_MODER_MODER13_1 
                  | ~GPIO_MODER_MODER14_1 | ~GPIO_MODER_MODER15_1);
   //Set PUSH-PULL (OTYPER 0)               
   GPIOE->OTYPER &= (~GPIO_OSPEEDER_OSPEEDR8_0 | ~GPIO_OTYPER_OT_9 | ~GPIO_OTYPER_OT_10
                  | ~GPIO_OTYPER_OT_11 | ~GPIO_OTYPER_OT_12 | ~GPIO_OTYPER_OT_13
                  | ~GPIO_OTYPER_OT_14 | ~GPIO_OTYPER_OT_15);
   
   //Set High speed (OSPEEDER 11)
   GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_0 | GPIO_OSPEEDER_OSPEEDR8_1 | GPIO_OSPEEDER_OSPEEDR9_0 | GPIO_OSPEEDER_OSPEEDR9_1
                  | GPIO_OSPEEDER_OSPEEDR10_0 | GPIO_OSPEEDER_OSPEEDR10_1 | GPIO_OSPEEDER_OSPEEDR11_0 | GPIO_OSPEEDER_OSPEEDR11_1
                  | GPIO_OSPEEDER_OSPEEDR12_0 | GPIO_OSPEEDER_OSPEEDR12_1 | GPIO_OSPEEDER_OSPEEDR13_0 | GPIO_OSPEEDER_OSPEEDR13_1
                  | GPIO_OSPEEDER_OSPEEDR14_0 | GPIO_OSPEEDER_OSPEEDR14_1 | GPIO_OSPEEDER_OSPEEDR15_0 | GPIO_OSPEEDER_OSPEEDR15_1;
   
   //Set nopullup-nopulldown (PUPDR 00)
   GPIOE->PUPDR &= ( ~GPIO_PUPDR_PUPDR8_0 | ~GPIO_PUPDR_PUPDR8_1 | ~GPIO_PUPDR_PUPDR9_0 | ~GPIO_PUPDR_PUPDR9_1
                  | ~GPIO_PUPDR_PUPDR10_0 | ~GPIO_PUPDR_PUPDR10_1 | ~GPIO_PUPDR_PUPDR11_0 | ~GPIO_PUPDR_PUPDR11_1
                  | ~GPIO_PUPDR_PUPDR12_0 | ~GPIO_PUPDR_PUPDR12_1 | ~GPIO_PUPDR_PUPDR13_0 | ~GPIO_PUPDR_PUPDR13_1
                  | ~GPIO_PUPDR_PUPDR14_0 | ~GPIO_PUPDR_PUPDR14_1 | ~GPIO_PUPDR_PUPDR15_0 | ~GPIO_PUPDR_PUPDR15_1);
                  
}

   /*** GPIOA Button PA0 Init ***/
static void GPIOA_BUTTON_Init(void){
   // Enabled clock for GPIOA
   RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
   
   /*** config PA0 as pushpull input ***/   
   //Set as Input (MODER 00)
   GPIOA->MODER &= (~GPIO_MODER_MODER0_0 | ~GPIO_MODER_MODER0_1);
  
   //Set PUSH-PULL (OTYPER 0)
   GPIOA->OTYPER &= ~GPIO_OTYPER_OT_0;
   
   //Set Low-speed (OSPEEDER x0)
   GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR0_0;
   
   //Set nopullup-nopulldown (PUPDR 00)
   GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0_0 | ~GPIO_PUPDR_PUPDR0_1;

   /*** Interrupt config ***/
   SYSCFG->EXTICR[1] |= SYSCFG_EXTICR1_EXTI0_PA;   //podlaczenie PA0 do lini EXTI0
   EXTI->IMR |= EXTI_IMR_MR0;                      // IRM - interrupt mask register - wlaczenie maskowania dla lini EXTI0 
   EXTI->RTSR |= EXTI_RTSR_RT0;                    // RTSR - Raising Trigger Selection register
   NVIC_SetPriority(EXTI0_IRQn, 7);
   NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI0_IRQHandler(void){
   static uint16_t button_pressed = 0;
   static uint16_t button_unpressed = 0;
   static uint16_t debounce_value = 10;
   static uint8_t wait_for_next_press = 0;
   
   if((EXTI->PR & EXTI_PR_PR0) == EXTI_PR_PR0){
      //SW eliminacja drgania stykow
      if (((GPIOA->IDR) & GPIO_IDR_0 ) == GPIO_IDR_0){
         button_pressed++;
         button_unpressed = 0;
         if (button_pressed > debounce_value && wait_for_next_press == 0){
            if(!CheckButtonState(ButtonPressedLongerToGoStandby)) ChangeButtonState(JustPressed);
            wait_for_next_press = 1;
            //EXTI->PR |= EXTI_PR_PR0;
         }             
      } else{
         button_unpressed++;
         button_pressed = 0;
         if (button_unpressed>debounce_value && wait_for_next_press == 1) {         
            wait_for_next_press =0;
            EXTI->PR |= EXTI_PR_PR0;
         }
      }  
   }
}

void GPIO_Init(void){
   GPIOE_LED_Init();
   GPIOA_BUTTON_Init();
}


