#include "../headers/LedControl.h"

/*       
                    [5] LD10(PE13) N
          [4] LD9(PE12) NW          [6] LD8(PE14) NE
 [3] LD7(PE11) W                             [7] LD6(PE15) E
          [2] LD5(PE10) SW          [0] LD4(PE8) SE
                    [1] LD3(PE9) S
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

void SetAllLedsBlinkOn(void){
   for (int i=0; i<NumberOfLeds; i++){
      tLedStatus[i].blink=True;
   } 
}

void SetAllLedsBlinkOff(void){
   for (int i=0; i<NumberOfLeds; i++){
      tLedStatus[i].blink=False;
   } 
}



