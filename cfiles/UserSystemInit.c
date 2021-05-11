#include "../headers/UserSystemInit.h"

static volatile uint32_t timer_ms;

void ClockConfig_HSE_with_PLL(void){

   RCC->CR |= RCC_CR_HSEBYP;                          
   RCC->CR |= RCC_CR_HSEON;
   
   uint16_t i=0;                                      //zmienna pomocnicza - zliczenie cykli po jakim czasie zegar HSE bedzie gotowy 
   while ((RCC->CR & RCC_CR_HSERDY) != 0x20000) i++;  // oczekiwanie az zordlo HSE bedzie stabilne - zmienna i pokazuje mi jak dlugo trwala 
   
   // konfig pentli PLL
   RCC->CR &= ~RCC_CR_PLLON; 
   RCC->CFGR |= RCC_CFGR_PLLXTPRE_HSE_PREDIV_DIV1; 
   RCC->CFGR |= RCC_CFGR_PLLSRC_HSE_PREDIV;
   RCC->CFGR |= RCC_CFGR_PLLMUL9;   
   RCC->CR |= RCC_CR_PLLON;
   
   uint16_t w=0;
   while ((RCC->CR & RCC_CR_PLLRDY) != 0x2000000) w++;
   
   //Ustawienie zegarow APB1, APB2, USB, I2C, SYSCLK
   RCC->CFGR |= RCC_CFGR_USBPRE_DIV1_5;
   RCC->CFGR |= RCC_CFGR_I2SSRC_SYSCLK ;
   RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
   RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
   RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
   
   //Ustawienie dzielnika 4 na ADC 1 i 2
   RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV4;
   
   //flash ustawienie opoznienia 2 cykli
   FLASH->ACR |= FLASH_ACR_LATENCY_1;
   
   //Wlaczenie sygnalu z PLL jako glownego zrodla taktowania
   RCC->CFGR |= RCC_CFGR_SW_PLL;
   SysTick_Config(72000000/1000);
   
}

void SysTick_Handler(void){     
   if (timer_ms) timer_ms--;
}

void delay_ms(uint32_t time){
   timer_ms=time;
   while(timer_ms);
}

void GoSleep (void){   
   StandbyConfig();       
   __WFI(); // wait for interrupt   
}
   
   
void StandbyConfig(void){
  /*** Standby Mode ***/
   SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;   
   RCC->APB1ENR |= RCC_APB1ENR_PWREN;
   PWR->CR |= PWR_CR_PDDS;
   PWR->CR |= PWR_CR_CWUF;
   PWR->CSR |= PWR_CSR_EWUP1;
   TIM7_config();
   TIM7->CR1 |= TIM_CR1_CEN;                          // Wlaczenie licznika TIM
}   


void SystemSetup (void) {
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
   InitStruct_LedsStatus_tab();
   TIM8_config();
   
   /*** TurnOn All Timers ***/
   TurnOnTimers();   
}

