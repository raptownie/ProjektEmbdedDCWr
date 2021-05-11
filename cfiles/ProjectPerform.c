#include "../headers/ProjectPerform.h"

static const MainState_t StateAfterTurnOnDevice = AfterWakeUpState; // do not change 

static MainState_t MainState = StateAfterTurnOnDevice;
static ButtonState_t ButtonState = Unpressed;


void MainStatePerform(void){
   switch (MainState){
      case GyroState:
         if (ButtonIsPressedBy_ms(TimeToTurnOnOffDevice_ms)) ChangeMainState(GoStandbyState);
         if (CheckButtonPressed()) ChangeMainState(AcceleroState);
         break;
      case AcceleroState:
         if (ButtonIsPressedBy_ms(TimeToTurnOnOffDevice_ms)) ChangeMainState(GoStandbyState);         
         if (CheckButtonPressed()) ChangeMainState(GyroState);
         break;
      case AfterWakeUpState:
         if (ButtonIsPressedBy_ms(TimeToTurnOnOffDevice_ms)) {
            ClearStandbyFlag();
            DeviceAfterWakeUpLedShow();
            ChangeMainState(GyroState);
         }else if(ButtonIsUnpressed()) GoSleep();
         break;
      case GoStandbyState:
         if ((ButtonIsPressedBy_ms(TimeToTurnOnOffDevice_ms))){
            GoStandbyModeDeviceLedShow();
            GoSleep();
         }
         break;
   }
}

void ButtonStatePerform(void){
   switch (ButtonState){
      case JustPressed:       // w ten stan wchodzi w przerwaniu, jak to zrobic sensownie inaczej idk?
         break;
      case Unpressed:         // po odczycie stanu wcisnietego przycisku przechodzi w stan upressed    
         break;
      case ButtonPressedLongerToGoStandby:
         MainState = GoStandbyState;
         break;
   }
}

bool CheckButtonPressed(void){   
   if (CheckButtonState(JustPressed)){
      ChangeButtonState(Unpressed);
      return true;
   }   
   return false;
}

void ChangeButtonState (ButtonState_t ChooseButtonState){
   ButtonState = ChooseButtonState;
}

bool CheckButtonState (ButtonState_t StateToCheck){
   if (StateToCheck == ButtonState) return true;
   return false;
}

void ChangeMainState (MainState_t ChooseMainState){   
   MainState = ChooseMainState;
}

bool CheckMainState (MainState_t MainStateToCheck){
   if(MainState == MainStateToCheck) return true;
   return false;
}

bool ButtonIsPressedBy_ms (uint32_t time_ms){
   if (time_ms < (HowLongButtonIsPressed*100)) return true;
   return false;
}

bool ButtonIsUnpressed (void){
   if (((GPIOA->IDR) & GPIO_IDR_0 ) != GPIO_IDR_0) return true;
   return false;
}

void ClearStandbyFlag(void){
   PWR->CR |= PWR_CR_CSBF;
}
