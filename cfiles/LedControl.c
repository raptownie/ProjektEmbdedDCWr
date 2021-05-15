#include "../headers/LedControl.h"

LedStatus_t tLedStatus[NumberOfLeds];

static void Set_GPIO_ODR (uint32_t );
static void Clear_GPIO_ODR (uint32_t );
static void SequenceLedAfterWakeUp (LedStatus_t *);
static void SequenceLedGoToStandby (LedStatus_t *);

static int TurnOffLedSequence[] = TurnOffLedSequenceDate;
static int TurnOnLedSequence[] = TurnOnLedSequenceDate;

static bool TurnOnLedSequenceFinishFlag = false;
static bool TurnOffLedSequenceFinishFlag = false;
bool *pTurnOnLedSequenceFinishFlag = &TurnOnLedSequenceFinishFlag;
bool *pTurnOffLedSequenceFinishFlag = &TurnOffLedSequenceFinishFlag;

void InitStruct_LedsStatus_tab (LedStatus_t *LedStruct){
   LedStruct[0].Pin_ODR = LD3_ODR_BIT;
   LedStruct[1].Pin_ODR = LD4_ODR_BIT;
   LedStruct[2].Pin_ODR = LD5_ODR_BIT;
   LedStruct[3].Pin_ODR = LD6_ODR_BIT;
   LedStruct[4].Pin_ODR = LD7_ODR_BIT;
   LedStruct[5].Pin_ODR = LD8_ODR_BIT;
   LedStruct[6].Pin_ODR = LD9_ODR_BIT;
   LedStruct[7].Pin_ODR = LD10_ODR_BIT;
   AllLedsOff(LedStruct);   
}

void DisplayShow (LedStatus_t *LedStruct){
   SequenceLedAfterWakeUp(LedStruct);
   SequenceLedGoToStandby(LedStruct);
   for (int i=0; i<NumberOfLeds; i++){      
      if (LedStruct[i].OnOffStatus == On) {
         Set_GPIO_ODR(tLedStatus[i].Pin_ODR);         
      }else {
         Clear_GPIO_ODR(tLedStatus[i].Pin_ODR);
      }      
   }   
}

void AllLedsOff(LedStatus_t *LedStruct){
   for (int i=0; i<NumberOfLeds; i++){
      LedStruct[i].OnOffStatus = Off;
      LedStruct[i].blink = false;
   }
}

void AllLedsOn(LedStatus_t *LedStruct){
   for (int i=0; i<NumberOfLeds; i++){
      LedStruct[i].OnOffStatus = On;
   }   
}

void SetLedOn(LedStatus_t *LedStruct, uint8_t LedToTurnOn){
  LedStruct[LedToTurnOn].OnOffStatus = On;      
}

void SetLedOff(LedStatus_t *LedStruct, uint8_t LedToTurnOff){
   LedStruct[LedToTurnOff].OnOffStatus = Off;   
}

void BlinkLed(LedStatus_t *LedStruct){
   static uint8_t EvenOddCount = 0;
   if (EvenOddCount++%2){
      for (int i=0; i<NumberOfLeds; i++){
            if (LedStruct[i].blink==true) LedStruct[i].OnOffStatus = On;
      }
   }else{
      for (int i=0; i<NumberOfLeds; i++){
            if (LedStruct[i].blink==true) LedStruct[i].OnOffStatus = Off;
      }      
   }
}

void SetLedBlinkOn(LedStatus_t *LedStruct, uint8_t LedToBlinkOn ){
   LedStruct[LedToBlinkOn].blink = true;   
}

void SetLedBlinkOff(LedStatus_t *LedStruct, uint8_t LedToBlinkOff){
   LedStruct[LedToBlinkOff].blink = false;
}

void SetAllLedsBlinkOn(LedStatus_t *LedStruct){
   for (int i=0; i<NumberOfLeds; i++){
      LedStruct[i].blink=true;
   } 
}

void SetAllLedsBlinkOff(LedStatus_t *LedStruct){
   for (int i=0; i<NumberOfLeds; i++){
      LedStruct[i].blink=false;
   } 
}

static void Set_GPIO_ODR (uint32_t GPIO_ODR){
   GPIOx_ODR |= GPIO_ODR;   
}

static void Clear_GPIO_ODR (uint32_t GPIO_ODR){
   GPIOx_ODR &= ~GPIO_ODR;
}

static void SequenceLedAfterWakeUp (LedStatus_t *LedStruct){
   
   static uint32_t SaveCurrentTimeTurnOnOffSequence = 0;
   static uint8_t TurnOnOffIncreament = 0;      
   static bool firstRun = true;
   
   if (CheckMainState(AfterWakeUpState) && *pTurnOnLedSequenceStartFlag){         
      if (firstRun){
         firstRun = false;
         AllLedsOff(LedStruct);
      }
      if ((timer_ms - SaveCurrentTimeTurnOnOffSequence) >= TurnOnOffLedSequenceDelay){
         LedStruct[TurnOnLedSequence[TurnOnOffIncreament++]].OnOffStatus = On;
         SaveCurrentTimeTurnOnOffSequence=timer_ms;
         if (TurnOnOffIncreament == (NumberOfLeds)){            
            TurnOnOffIncreament = 0;
            SaveCurrentTimeTurnOnOffSequence = 0;
            TurnOnLedSequenceFinishFlag = true;
         }
      }    
   }
}

static void SequenceLedGoToStandby (LedStatus_t *LedStruct){
   
   static uint32_t SaveCurrentTimeTurnOnOffSequence = 0;
   static uint8_t TurnOnOffIncreament = 0;
   static bool firstRun = true;
   
   if (CheckMainState(GoStandbyState) && *pTurnOffLedSequenceStartFlag){
      if (firstRun) {
         AllLedsOn(LedStruct);
         firstRun = false;
      }
      if ((timer_ms - SaveCurrentTimeTurnOnOffSequence) >= TurnOnOffLedSequenceDelay){
         LedStruct[TurnOffLedSequence[TurnOnOffIncreament++]].OnOffStatus = Off;
         SaveCurrentTimeTurnOnOffSequence=timer_ms;
         if (TurnOnOffIncreament == (NumberOfLeds)){
            TurnOnOffIncreament = 0;
            SaveCurrentTimeTurnOnOffSequence = 0;
            TurnOffLedSequenceFinishFlag = true;
         }
      }
   }
   
}
