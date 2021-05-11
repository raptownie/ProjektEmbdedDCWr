#include "../headers/LedControl.h"

/*       
                    [5] LD10(PE13) N
          [4] LD9(PE12) NW          [6] LD8(PE14) NE
 [3] LD7(PE11) W                             [7] LD6(PE15) E
          [2] LD5(PE10) SW          [0] LD4(PE8) SE
                    [1] LD3(PE9) S
*/


LedStatus_t tLedStatus[NumberOfLeds];

static void Set_GPIO_ODR (uint32_t );
static void Clear_GPIO_ODR (uint32_t );

void InitStruct_LedsStatus_tab (void){
   tLedStatus[0].Pin_ODR = LD4_ODR_BIT;
   tLedStatus[1].Pin_ODR = LD3_ODR_BIT;
   tLedStatus[2].Pin_ODR = LD5_ODR_BIT;
   tLedStatus[3].Pin_ODR = LD7_ODR_BIT;
   tLedStatus[4].Pin_ODR = LD9_ODR_BIT;
   tLedStatus[5].Pin_ODR = LD10_ODR_BIT;
   tLedStatus[6].Pin_ODR = LD8_ODR_BIT;
   tLedStatus[7].Pin_ODR = LD6_ODR_BIT;
   AllLedsOff();   
}

void DisplayShow (void){
    for (int i=0; i<NumberOfLeds; i++){
      if (tLedStatus[i].OnOffStatus == On) {
         Set_GPIO_ODR(tLedStatus[i].Pin_ODR);         
      }else {
         Clear_GPIO_ODR(tLedStatus[i].Pin_ODR);
      }      
   }   
}

void AllLedsOff(void){
   for (int i=0; i<NumberOfLeds; i++){
      tLedStatus[i].OnOffStatus = Off;
      tLedStatus[i].blink = false;
   }
}

void AllLedsOn(void){
   for (int i=0; i<NumberOfLeds; i++){
      tLedStatus[i].OnOffStatus = On;
   }   
}

void SetLedOn(LedStatus_t *LedStruct, uint8_t LedToTurnOn){
  LedStruct[LedToTurnOn].OnOffStatus = On;      
}

void SetLedOff(LedStatus_t *LedStruct, uint8_t LedToTurnOff){
   LedStruct[LedToTurnOff].OnOffStatus = Off;   
}

void BlinkLed(void){
   static uint8_t EvenOddCount = 0;
   if (EvenOddCount++%2){
      for (int i=0; i<NumberOfLeds; i++){
            if (tLedStatus[i].blink==true)tLedStatus[i].OnOffStatus = On;
      }
   }else{
      for (int i=0; i<NumberOfLeds; i++){
            if (tLedStatus[i].blink==true)tLedStatus[i].OnOffStatus = Off;
      }      
   }
}

void SetLedBlinkOn(LedStatus_t *LedStruct, uint8_t LedToBlinkOn ){
   LedStruct[LedToBlinkOn].blink = true;   
}

void SetLedBlinkOff(LedStatus_t *LedStruct, uint8_t LedToBlinkOff){
   LedStruct[LedToBlinkOff].blink = false;
}

void SetAllLedsBlinkOn(void){
   for (int i=0; i<NumberOfLeds; i++){
      tLedStatus[i].blink=true;
   } 
}

void SetAllLedsBlinkOff(void){
   for (int i=0; i<NumberOfLeds; i++){
      tLedStatus[i].blink=false;
   } 
}

void GoStandbyModeDeviceLedShow(void){
   AllLedsOn();   
   for (int i=0; i<NumberOfLeds; i++){
         delay_ms(500);
      tLedStatus[i].OnOffStatus = Off;
   }   
      delay_ms(500);
      
   
}

void DeviceAfterWakeUpLedShow(void){
    for (int i=0; i<NumberOfLeds; i++){
         delay_ms(500);
      tLedStatus[i].OnOffStatus = On;
   }   
      delay_ms(500);
      AllLedsOff();
}


static void Set_GPIO_ODR (uint32_t GPIO_ODR){
   GPIOx_ODR |= GPIO_ODR;   
}

static void Clear_GPIO_ODR (uint32_t GPIO_ODR){
   GPIOx_ODR &= ~GPIO_ODR;
}

