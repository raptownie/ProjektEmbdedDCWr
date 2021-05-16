#include "../headers/ProjectPerform.h"

static const MainState_t StateAfterTurnOnDevice = AfterWakeUpState; // do not change 

static MainState_t MainState = StateAfterTurnOnDevice;
static ButtonState_t ButtonState = Unpressed;

static bool TurnOnLedSequenceStartFlag = false;
static bool TurnOffLedSequenceStartFlag = false;
bool *pTurnOnLedSequenceStartFlag = &TurnOnLedSequenceStartFlag;
bool *pTurnOffLedSequenceStartFlag = &TurnOffLedSequenceStartFlag;

static bool ButtonIsPressed(void);
static void UnpressedStateHandling(void);
static void PressedStateHandling(void);
static void ButtonIsPressedLongerGoStandbyOrWakeupStateHandling(void);
static void ChangeButtonState (ButtonState_t );
static bool CheckButtonState (ButtonState_t );
static void ChangeMainState (MainState_t );
static bool ButtonIsPressedBy_ms (uint32_t );
static void ClearStandbyFlag(void);
static bool ButtonIsUnpressed (void);



void MainStatePerform(void){
   switch (MainState){
      case GyroState:
         if (CheckButtonState(ButtonIsPressedLongerGoStandbyOrWakeupState)) 
            ChangeMainState(GoStandbyState);   
         if (CheckButtonState(Pressed)) 
            ChangeMainState(AcceleroState);
         break;
      case AcceleroState:
         if (CheckButtonState(ButtonIsPressedLongerGoStandbyOrWakeupState)) 
            ChangeMainState(GoStandbyState);         
         if (CheckButtonState(Pressed)) 
            ChangeMainState(GyroState);
         break;
      case AfterWakeUpState:
         if (CheckButtonState(ButtonIsPressedLongerGoStandbyOrWakeupState) || TurnOnLedSequenceStartFlag) {            
            TurnOnLedSequenceStartFlag = true;
            if (*pTurnOnLedSequenceFinishFlag){
               ClearStandbyFlag();
               AllLedsOff(LedStructName);
               TurnOnLedSequenceStartFlag = false;
               ChangeMainState(MainStateAfterWakeUp);
            }                    
         }else if (ButtonIsUnpressed())GoSleep();
         break;
      case GoStandbyState:
         if (CheckButtonState(ButtonIsPressedLongerGoStandbyOrWakeupState) || TurnOffLedSequenceStartFlag){
            TurnOffLedSequenceStartFlag = true;
            if(*pTurnOffLedSequenceFinishFlag) GoSleep(); 
         }
         break;
   }
}

void ButtonStatePerform(void){
   switch (ButtonState){
      case Pressed:      
         PressedStateHandling();         
         break;
      case Unpressed:         
         UnpressedStateHandling();
         break;
      case ButtonIsPressedLongerGoStandbyOrWakeupState:
         ButtonIsPressedLongerGoStandbyOrWakeupStateHandling();
         break;
   }
}



static void ChangeButtonState (ButtonState_t ChooseButtonState){
   ButtonState = ChooseButtonState;
}

static bool CheckButtonState (ButtonState_t StateToCheck){
   if (StateToCheck == ButtonState) return true;
   return false;
}

static void ChangeMainState (MainState_t ChooseMainState){   
   MainState = ChooseMainState;
}

bool CheckMainState (MainState_t MainStateToCheck){
   if(MainState == MainStateToCheck) return true;
   return false;
}

static bool ButtonIsPressedBy_ms (uint32_t time){
   
   static uint32_t HowLongButtonIsPressed_ms = 0;
   static volatile bool firstRunFlag = true;
   
   if (ButtonIsPressed()){  
      if (firstRunFlag){
         HowLongButtonIsPressed_ms = timer_ms;
         firstRunFlag = false;
      }else if ((timer_ms - HowLongButtonIsPressed_ms) > time){
         firstRunFlag = true;
         return true;
      }       
      return false;
   }
   firstRunFlag = true;
   return false;
   }   


static bool ButtonIsUnpressed (void){
   if (((GPIOA->IDR) & GPIO_IDR_0 ) != GPIO_IDR_0) return true;
   return false;
}

static bool ButtonIsPressed(void){
   if (((GPIOA->IDR) & GPIO_IDR_0 ) == GPIO_IDR_0) return true;
   return false;
}

static void ClearStandbyFlag(void){
   PWR->CR |= PWR_CR_CSBF;
}

static void UnpressedStateHandling(void){
   
   static uint8_t count= 0;
   if (ButtonIsPressed()){
      if (count++>DebounceValue)
            ChangeButtonState(Pressed);
      } else 
         count = 0;
}

static void PressedStateHandling(void){
   static MainState_t LastState;
 //  static uint8_t count = 0;
   if(ButtonIsUnpressed() && (LastState != MainState)){
      
      ChangeButtonState(Unpressed);
      LastState = MainState;       
   }else if (ButtonIsPressed() && ButtonIsPressedBy_ms(TimeToTurnOnOffDevice_ms)){
      ChangeButtonState(ButtonIsPressedLongerGoStandbyOrWakeupState);
   }
}

static void ButtonIsPressedLongerGoStandbyOrWakeupStateHandling(void){
   if ((MainState != AfterWakeUpState) && (MainState != GoStandbyState))
      ChangeButtonState(Unpressed);
   
}
