#include "../headers/SPI.h"


static int8_t SPI_L3GD2_YL;
static int8_t SPI_L3GD2_YH;
static int8_t SPI_L3GD2_ZL;
static int8_t SPI_L3GD2_ZH;
static int8_t SPI_L3GD2_XL;
static int8_t SPI_L3GD2_XH;


void SPI_Config_for_Gyroskop(void){
   
   //konfiguracja pinow GPIO SCK, MOSI, MISO, CS
   RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
   GPIOA->MODER |= GPIO_MODER_MODER5_1;   // PA5 SCK - set alternate func
   GPIOA->MODER |= GPIO_MODER_MODER6_1;   // PA6 MOSI - set alternate func
   GPIOA->MODER |= GPIO_MODER_MODER7_1;   // PA7 MISO - set alternate func
   
   GPIOA->AFR[0] |= (0x5 << GPIO_AFRL_AFRL5_Pos) | (0x5 << GPIO_AFRL_AFRL6_Pos) | (0x5 << GPIO_AFRL_AFRL7_Pos);         // AF5 dla PA5,6,7
   
   RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
   GPIOE->MODER |= GPIO_MODER_MODER3_0;   // PE3 CS - set as aoutput
   GPIOE->OTYPER &= ~GPIO_OTYPER_OT_3;    // PE3 output push pull
   GPIOE->ODR |= GPIO_ODR_3;
   
   //konfiguracja SPI
   RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
   SPI1->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0;             //konfiguracja zegara SCK - dla ukladu L3GD20 max 10MHz - taktowanie SYSCLK 72MHz -  a wiec dzielnik 8 czyli 010 = 9MHz
   SPI1->CR1 |= SPI_CR1_CPHA;             // jak wynika z doc L3GD20 musi byc opoznienie danych o jeden cykl zegarowy
   SPI1->CR1 |= SPI_CR1_CPOL;             //polaryzacja zegara SCK  - dokumentacja L3GD20 mowi ze musi byc stan wysoki w IDLE
   SPI1->CR1 &= ~SPI_CR1_RXONLY;          // full duplex

   SPI1->CR1 &= ~SPI_CR1_LSBFIRST;        // set MSB frame format (most significant bit)
   SPI1->CR1 |= SPI_CR1_MSTR;             // master configuration

   
   SPI1->CR2 |= SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2; // data length transfer 8 bit 0111;
   SPI1->CR2 |= SPI_CR2_SSOE;             //1: SS output is enabled in master mode and when the SPI interface is enabled. 
   SPI1->CR2 &= ~SPI_CR2_FRF;             // Frame format  - 0: SPI Motorola mode   ????? !!brak info w dokumentacji!!
   SPI1->CR2 |= SPI_CR2_FRXTH;            //FIFO reception threshold 8bit

   GPIOE->ODR |= GPIO_ODR_3;        // Slave Selector SS disable
   
   SPI_L3GD20_Init();
   Timers_TIM6_config();
}


//ta funkcja jeszcze nie dziala
void SPI_Write(uint8_t reg, uint8_t data){
   
   GPIOE->ODR &= ~GPIO_ODR_3;  
   SPI1->CR1 |= SPI_CR1_SPE;  
   while (!(SPI1->SR & SPI_SR_TXE));  
   reg= (reg | 0x40);
   SPI1->DR = (uint32_t)((data<<8) | reg);
   while (!(SPI1->SR & SPI_SR_TXE));
   while (SPI1->SR & SPI_SR_BSY);
   while(!(SPI1->SR & SPI_SR_RXNE));
   SPI1->CR1 &= ~SPI_CR1_SPE;
   GPIOE->ODR |= GPIO_ODR_3;        // Slave Selector SS 
}

uint8_t SPI_Read(uint8_t reg){
   GPIOE->ODR &= ~GPIO_ODR_3;        // Slave Selector SS 
   SPI1->CR1 |= SPI_CR1_SPE;           // wlaczamy SPI
   while (SPI1->SR & SPI_SR_BSY);      // czy SPI zajety?
   while (!(SPI1->SR & SPI_SR_TXE));      // sprawdzenie czy kolejka TX jest pusta
   SPI1->DR = (0xC0|reg);              // trzeba wlaczyc BIT 8 i 7  (8-read, 7-When 0 do not increment address; when 1 increment address in multiple reading.
   while (!(SPI1->SR & SPI_SR_TXE));   // czekamy az zakonczy wysylanie
   while (SPI1->SR & SPI_SR_BSY);      // sprawdzamy czy SPI jest zajety
  // SPI1->DR= 0x00;                     // dummy read
   while(!(SPI1->SR & SPI_SR_RXNE));   // czekamy na odpowiedz
   volatile uint8_t rd = (uint8_t) SPI1->DR;     // za pierwszym razem odczytuje FF, wiec dodalem odczyt przed wlasciwym odczytem zeby zdjac z kolejki FIFO  
   while(!(SPI1->SR & SPI_SR_RXNE));   // znowu sprawdzamy czy jest jakas dana do odczytu w buforze
   uint8_t r= (uint8_t)SPI1->DR;       // odczyt wlasciwy
   SPI1->CR1 &= ~SPI_CR1_SPE;          //wylaczamy spi
   GPIOE->ODR |= GPIO_ODR_3;        // Slave Selector SS 
   return r;
}

void SPI_L3GD20_Init(void){
   
   SPI_Read(0x0F);          
   // axis xyz on, power on
   SPI_Write(0x20, 0xF);      
   SPI_Read(0x20);   
   SPI_Write(0x23, 0xF0);    // output registers not updated until MSb and LSb readinge; set 500 DPS

}

void SPI_Gyroskop_L3GD20_XYZ_Read_Calculate(void){
     
   SPI_L3GD2_YL = (int8_t)SPI_Read(L3GD20_Reg_YL);   
   SPI_L3GD2_YH = (int8_t)SPI_Read(L3GD20_Reg_YH);   
   GyroskopXYZvalues.values.Y_value = (int16_t)(SPI_L3GD2_YL |(SPI_L3GD2_YH << 8));

   SPI_L3GD2_ZL = (int8_t)SPI_Read(L3GD20_Reg_ZL);  
   SPI_L3GD2_ZH = (int8_t)SPI_Read(L3GD20_Reg_ZH);   
   GyroskopXYZvalues.values.Z_value = (int16_t)(SPI_L3GD2_ZL |(SPI_L3GD2_ZH <<8));

   SPI_L3GD2_XL = (int8_t)SPI_Read(L3GD20_Reg_XL); 
   SPI_L3GD2_XH = (int8_t)SPI_Read(L3GD20_Reg_XH);      
   GyroskopXYZvalues.values.X_value = (int16_t)(SPI_L3GD2_XL | (SPI_L3GD2_XH << 8)); 
  
}
