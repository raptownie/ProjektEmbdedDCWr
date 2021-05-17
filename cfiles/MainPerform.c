#include "../headers/MainPerform.h"

static const MainState_t StateAfterTurnOnDevice = AfterWakeUpState; // do not change 

static MainState_t MainState = StateAfterTurnOnDevice;

static bool StateSwitchIsAvailable = false;


static void ClearStandbyFlag(void);
static void ChangeMainState (MainState_t );


void MainPerform_MainStatePerform(void){
   switch (MainState){
      case GyroState:
         if (ButtonPerform_CheckButtonState(ButtonIsPressedLongerGoStandbyOrWakeUpState)) 
            ChangeMainState(GoStandbyState);   
         if (ButtonPerform_CheckButtonState(Pressed) && StateSwitchIsAvailable){
            StateSwitchIsAvailable = false;
            ChangeMainState(AcceleroState);
         }
         if (ButtonPerform_CheckButtonState(Unpressed)) StateSwitchIsAvailable = true;
         break;
      case AcceleroState:
         if (ButtonPerform_CheckButtonState(ButtonIsPressedLongerGoStandbyOrWakeUpState)) 
            ChangeMainState(GoStandbyState);         
         if (ButtonPerform_CheckButtonState(Pressed) && StateSwitchIsAvailable){
            StateSwitchIsAvailable = false;
            ChangeMainState(GyroState);
         }
         if (ButtonPerform_CheckButtonState(Unpressed)) StateSwitchIsAvailable = true;
         break;
      case AfterWakeUpState:
         if (ButtonPerform_CheckButtonState(ButtonIsPressedLongerGoStandbyOrWakeUpState)) {
            ClearStandbyFlag();            
            ChangeMainState(LedAnimationAfterWakeUpState);                    
         }else if (ButtonPerform_ButtonIsUnpressed())
            ChangeMainState(SleepState);
         break;
      case GoStandbyState:
        if (ButtonPerform_CheckButtonState(ButtonIsPressedLongerGoStandbyOrWakeUpState))
           ChangeMainState(LedAnimationGoStandbyState);                 
         break;
      case LedAnimationAfterWakeUpState:
         if(LedControl_SequenceLedAfterWakeUpDone()) 
            ChangeMainState(MainStateAfterWakeUp);
         break;
      case LedAnimationGoStandbyState:
         if(LedControl_SequenceLedGoToStandbyDone()) 
            ChangeMainState(SleepState);
         break;
      case SleepState:
         GoSleep();
         break;
   }
}

static void ChangeMainState (MainState_t ChooseMainState){   
   MainState = ChooseMainState;
}

bool MainPerform_CheckMainState (MainState_t MainStateToCheck){
   if(MainState == MainStateToCheck) return true;
   return false;
}

static void ClearStandbyFlag(void){
   PWR->CR |= PWR_CR_CSBF;
}

