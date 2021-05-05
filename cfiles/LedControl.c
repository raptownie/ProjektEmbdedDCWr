#include "../headers/LedControl.h"

/*       
                    [5] LD10(PE13)
          [4] LD9(PE12)           [6] LD8(PE14)
 [3] LD7(PE11)                             [7] LD6(PE15)
          [2] LD5(PE10)           [0] LD4(PE8)
                    [1] LD3(PE9)
*/



LedStatus_t tLedStatus[NumberOfLeds];

void InitStruct_LedsStatus_t (void){
   AllLedsOff();   
}

void DisplayShow (void){
   for (int i=0; i<NumberOfLeds; i++){
      if (tLedStatus[i].OnOffStatus == On) {
         GPIOE->ODR |= (uint32_t)(0x1 << (i+8));
      }else {
         GPIOE->ODR &= ~(uint32_t)(0x1 << (i+8));
      }           
   }
}

void AllLedsOff(void){
   for (int i=0; i<NumberOfLeds; i++){
      tLedStatus[i].OnOffStatus = Off;
      tLedStatus[i].blink = False;
   }
}

void AllLedsOn(void){
   for (int i=0; i<NumberOfLeds; i++){
      tLedStatus[i].OnOffStatus = On;
   }   
}

void SetLedOn(LedStatus_t *Led){
   Led->OnOffStatus = On;   
}

void SetLedOff(LedStatus_t *Led){
   Led->OnOffStatus = Off;   
}

void BlinkLed(void){
   static int EvenOddCount = 0;
   if (EvenOddCount++%2){
      for (int i=0; i<NumberOfLeds; i++){
            if (tLedStatus[i].blink==True)tLedStatus[i].OnOffStatus = On;
      }
   }else{
      for (int i=0; i<NumberOfLeds; i++){
            if (tLedStatus[i].blink==True)tLedStatus[i].OnOffStatus = Off;
      }      
   }
}

void SetLedBlinkOn(LedStatus_t *Led){
   Led->blink = True;   
}

void SetLedBlinkOff(LedStatus_t *Led){
   Led->blink = False;   
}



