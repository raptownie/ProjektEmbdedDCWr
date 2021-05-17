#include "../headers/ButtonPerform.h"

static ButtonState_t ButtonState = Unpressed;


static void UnpressedStateHandling(void);
static void PressedStateHandling(void);
static void ButtonIsPressedLongerGoStandbyOrWakeupStateHandling(void);
static bool ButtonIsPressedBy_ms (uint32_t );
static void ChangeButtonState (ButtonState_t );


void ButtonPerform_ButtonStatePerform(void){
   switch (ButtonState){
      case Pressed:      
         PressedStateHandling();         
         break;
      case Unpressed:         
         UnpressedStateHandling();
         break;
      case ButtonIsPressedLongerGoStandbyOrWakeUpState:
         ButtonIsPressedLongerGoStandbyOrWakeupStateHandling();
         break;
   }
}

static void ChangeButtonState (ButtonState_t ChooseButtonState){
   ButtonState = ChooseButtonState;
}

bool ButtonPerform_CheckButtonState (ButtonState_t StateToCheck){
   if (StateToCheck == ButtonState) return true;
   return false;
}

static bool ButtonIsPressedBy_ms (uint32_t time){
   
   static uint32_t HowLongButtonIsPressed_ms = 0;
   static volatile bool firstRunFlag = true;
   
   if (ButtonPerform_ButtonIsPressed()){  
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


bool ButtonPerform_ButtonIsUnpressed (void){
   if (((GPIOA->IDR) & GPIO_IDR_0 ) != GPIO_IDR_0) return true;
   return false;
}

bool ButtonPerform_ButtonIsPressed(void){
   if (((GPIOA->IDR) & GPIO_IDR_0 ) == GPIO_IDR_0) return true;
   return false;
}



static void UnpressedStateHandling(void){
   
   static uint8_t count= 0;
   if (ButtonPerform_ButtonIsPressed()){
      if (count++>DebounceValue)
            ChangeButtonState(Pressed);
   } else 
      count = 0;
   ButtonIsPressedBy_ms(TimeToTurnOnOffDevice_ms);
}

static void PressedStateHandling(void){
   static uint8_t count= 0;
   if (ButtonPerform_ButtonIsUnpressed()){
      if (count++>DebounceValue){
         ChangeButtonState(Unpressed);
         count = 0;
      }
   }else if(ButtonIsPressedBy_ms(TimeToTurnOnOffDevice_ms)){
      ChangeButtonState(ButtonIsPressedLongerGoStandbyOrWakeUpState);
      count = 0;
   }
}

static void ButtonIsPressedLongerGoStandbyOrWakeupStateHandling(void){
   static uint8_t count= 0;
   if (ButtonPerform_ButtonIsUnpressed()){
      if (count++>DebounceValue){
         ChangeButtonState(Unpressed);
         count = 0;
      }
   }   
}
