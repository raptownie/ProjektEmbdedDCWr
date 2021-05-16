#include "../headers/UART.h"

/*
Parametry UARTA:
Boundrate = 115200
Parity - disabled
Number of StopBit = 1
*/

uint8_t SizeOfDataToSendUART4;
uint8_t SizeOfDataToReciveUART4;
Mode_t ModeSelect;
DataToSendUART_t GyroskopXYZvalues;
DataToSendUART_t AcceleroXYZvalues;

static void UART4_DMA_TIM1_config(void);
static void PrepareDataToSendUART(DataToSendUART_t DataToSend);
static char StringToSendUART[UartMaxDataSizeToSend];
static char StringToReciveUART[UartMaxDataSizeToRecive];



void UART4_Init_with_DMA_TIM1(void){
    //UART4  - Rx->PC11; Tx->PC10 */
   /******* Konfiguracja GPIO *******/  
   RCC->AHBENR |= RCC_AHBENR_GPIOCEN;                                         // enabled RCC for GPIOC
   
   // Set AF mode for PC10 and PC11
   GPIOC->MODER |= GPIO_MODER_MODER10_1 | GPIO_MODER_MODER11_1; 
   GPIOC->MODER &= ~GPIO_MODER_MODER10_0 | ~GPIO_MODER_MODER11_0; 
   
   GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1 | GPIO_OSPEEDER_OSPEEDR10_0;
   GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11_1 | GPIO_OSPEEDER_OSPEEDR11_0;
   
   GPIOC->AFR[1] |= (5 << 8) | (5 << 12);                                     //UART TX/RX AF5 -> 0b0101 = 5   
   
   /****** Konfiguracja UART4*******/
   RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
   UART4->CR1 &= ~USART_CR1_M0 | ~(1U << 28);
   
   // PLCK1= HCLK/2 = 72MHz/2 = 36Mhz
   UART4->CR1 &= ~USART_CR1_OVER8;                                            // set oversampling 16;
   UART4->BRR = 0xEA6;                                                        // Baudrate = 115200; dla Oversamplingu 16 BRR = USARTDIV = PLCK1/Baudrate = 36000000/115200 = 312 = 0x138
   UART4->CR1 &= ~USART_CR1_PCE;                                              // disabled parity control
   UART4->CR2 &= ~USART_CR2_STOP_0 | ~USART_CR2_STOP_1;                       // set stop = 1bit
   
   //DMA 
   UART4->CR3 |= USART_CR3_DMAT;                                              // enabled DMA transmit
   UART4->CR3 |= USART_CR3_DMAR;
   UART4_DMA_TIM1_config();

   UART4->CR1 |= USART_CR1_TE;                                                //transmiter enabled
   UART4->CR1 |= USART_CR1_RE;                                                //receiver enabled
   UART4->CR1 |= USART_CR1_UE;                                                // enabled UART4
   
   TIM1_config();
}

static void UART4_DMA_TIM1_config(void){
     
   
   RCC->AHBENR |= RCC_AHBENR_DMA2EN;
      
   // DMA UART4_Tx config - DMA2 channel 5
   DMA2_Channel5->CPAR = (uint32_t)&UART4->TDR;
   DMA2_Channel5->CMAR = (uint32_t)StringToSendUART;   

   DMA2_Channel5 ->CCR &= ~DMA_CCR_MEM2MEM;       // disable Memory 2 memory transfer
   
   DMA2_Channel5->CNDTR = 0x0;   
   
   DMA2_Channel5->CCR |= DMA_CCR_PL_0;          //priority level - 11 - najwyzszy
   DMA2_Channel5->CCR &= ~DMA_CCR_PL_1;
   
   DMA2_Channel5->CCR &= ~DMA_CCR_MSIZE_0;       // memory size 8 bitow
   DMA2_Channel5->CCR &= ~DMA_CCR_MSIZE_1;
   DMA2_Channel5->CCR &= ~DMA_CCR_PSIZE_0;       // periph size 8bitów
   DMA2_Channel5->CCR &= ~DMA_CCR_PSIZE_1; 
   
   DMA2_Channel5->CCR |= DMA_CCR_MINC;         // Memory inc enabled
   DMA2_Channel5->CCR &= ~DMA_CCR_PINC;         // Periph inc disabled;
   
   DMA2_Channel5->CCR &= ~DMA_CCR_CIRC;          //circular mode disabled
   DMA2_Channel5->CCR |= DMA_CCR_DIR;          // read from memory to periph
 
   DMA2_Channel5->CCR |= DMA_CCR_EN;            //wlaczamy DMA po calej konfiguracji
   
   /************************************************************/
   
   // DMA UART4_RX config - DMA2 channel 3
   DMA2_Channel3->CPAR = (uint32_t)&UART4->RDR;
   DMA2_Channel3->CMAR = (uint32_t)StringToReciveUART;   

   DMA2_Channel3 ->CCR &= ~DMA_CCR_MEM2MEM;       // disable Memory 2 memory transfer
   
   DMA2_Channel3->CNDTR = 0x0;   
   
   DMA2_Channel3->CCR |= DMA_CCR_PL_0;          //priority level - 11 - najwyzszy
   DMA2_Channel3->CCR &= ~DMA_CCR_PL_1;
 
   DMA2_Channel3->CCR &= ~DMA_CCR_MSIZE_0;       // memory size 8 bitow
   DMA2_Channel3->CCR &= ~DMA_CCR_MSIZE_1;
   DMA2_Channel3->CCR &= ~DMA_CCR_PSIZE_0; 
   // periph size 8 bitów
   DMA2_Channel3->CCR &= ~DMA_CCR_PSIZE_1; 
   
   DMA2_Channel3->CCR |= DMA_CCR_MINC;         // Memory inc enabled
   DMA2_Channel3->CCR &= ~DMA_CCR_PINC;         // Periph inc disabled;
   
   DMA2_Channel3->CCR &= ~DMA_CCR_CIRC;          //circular mode disabled
   DMA2_Channel3->CCR &= ~DMA_CCR_DIR;          // read from periph to memory;
 
   DMA2_Channel3->CCR |= DMA_CCR_EN;            //wlaczamy DMA po calej konfiguracji
}
/*
void Send_Gyro_Date_XYZ_UART(void){
  //  SizeOfDataToSendUART4 =(uint8_t) sprintf(StringToSendUART,"X = %d    \n\rY = %d    \n\rZ = %d     \x1b[A\r\x1b[A\r", X_value, Y_value, Z_value );
   //SizeOfDataToSendUART4=(uint8_t)sizeof(StringToSendUART);
}
*/
void Send_Data_Gyro_Accelero_XYZ_UART(void){
   if (CheckMainState(AcceleroState)){      
      PrepareDataToSendUART(AcceleroXYZvalues);
   }else {      
      PrepareDataToSendUART(GyroskopXYZvalues);
   }
}

static void PrepareDataToSendUART(DataToSendUART_t DataToSend){ 
//\033[2J - clearscreen
//\x1b[A  - powrot linijke wyzej
   if(CheckMainState(AcceleroState)) 
      SizeOfDataToSendUART4 =(uint8_t) sprintf(StringToSendUART,"\033[2J Mode Accelero \n\r X = %d    \n\r Y = %d    \n\r Z = %d     \x1b[A\r\x1b[A\r\x1b[A\r", DataToSend.values.X_value, DataToSend.values.Y_value, DataToSend.values.Z_value);
   else if (CheckMainState (GyroState))
      SizeOfDataToSendUART4 =(uint8_t) sprintf(StringToSendUART,"\033[2J Mode Gyro \n\r X = %d    \n\r Y = %d    \n\r Z = %d     \x1b[A\r\x1b[A\r\x1b[A\r", DataToSend.values.X_value, DataToSend.values.Y_value, DataToSend.values.Z_value);
   else if (CheckMainState(AfterWakeUpState))
      SizeOfDataToSendUART4 =(uint8_t) sprintf(StringToSendUART,"\033[2J The Device wakes up\r");
   else if (CheckMainState(GoStandbyState)) 
      SizeOfDataToSendUART4 =(uint8_t) sprintf(StringToSendUART,"\033[2J Turning off the device\r");
}

void DMAHandleUART (void) {
         // UART4_Tx
      DMA2_Channel5->CCR &= ~DMA_CCR_EN;    
      DMA2_Channel5->CNDTR = SizeOfDataToSendUART4;
      DMA2_Channel5->CCR |= DMA_CCR_EN; 

      //UART4_Rx
      DMA2_Channel3->CCR &= ~DMA_CCR_EN; 
      DMA2_Channel3->CNDTR = SizeOfDataToReciveUART4; 
      DMA2_Channel3->CCR |= DMA_CCR_EN;
   
}

