#ifndef ConfigHeader
#define ConfigHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#define TimeToTurnOnOffDevice_ms 2500
#define UartMaxDataSizeToRecive 40
#define UartMaxDataSizeToSend 100

//Co ile bedzie generwoany impuls przerwania - obsluga standby
#define TIM7_Prescaler                 9999        // 72Mhz/(TIM7_Prescaler+1) - ilosc impulsow na 1s
#define TIM7_AutoReloadRegisterValue   1440         // co ile impulsów TIM7 ma generowac przerwanie 
#define TIM7Toms                       (1000*TIM7_AutoReloadRegisterValue/(ClockHZ/(TIM7_Prescaler+1)))   // takaby makro TimeToTurnOnOffDevice_ms dzialalo niezaleznie od parametrow licznika TIM7

//Co ile beda generwoane nowe wartosci gyroskopu/accelero
#define TIM6_Prescaler                 9999        // 72Mhz/(TIM6_Prescaler+1) - ilosc impulsow na 1s
#define TIM6_AutoReloadRegisterValue   144         // co ile impulsów TIM7 ma generowac przerwanie 

//CC1 - co ile impulsow bd uruchamiana funkcja tworzaca dane dla UARTa
//AutoReloadRegister - co ile bedzie wystepowac przerwanie wysylajace dane przez UARTA
#define TIM1_Prescaler                 9999       // 72Mhz/(TIM1_Prescaler+1) - ilosc impulsow na 1s
#define TIM1_AutoReloadRegisterValue   3600        // co ile impulsów TIM1 ma generowac przerwanie
#define TIM1_CCR1_value                2000       //co ile impulsow generowane jest przerwanie z kanalu pierwszego TIM1 
#define TIM1_CCR2_value                1       //CCR2 sluzy do wlaczeni BLINKa po Wakeup
#define TIM1_CCR3_value                1801       //CCR2 sluzy do wylaczeni BLINKa po Wakeup 

//licznik do odswiezania displaya
#define TIM8_Prescaler                 9999       // 72Mhz/(TIM8_Prescaler+1) - ilosc impulsow na 1s
#define TIM8_AutoReloadRegisterValue   72      // co ile impulsów TIM1 ma generowac przerwanie

#define ClockHZ 72000000

//Accelero registers adresses
#define Accelerometer_Adress 0x19
#define Accelero_CTRL_REG1_A_Adress 0x20
#define Accelero_CTRL_REG4_A_Adress 0x23
#define Accelero_OUT_X_H_A_Adress 0x29
#define Accelero_OUT_Y_H_A_Adress 0x2B
#define Accelero_OUT_Z_H_A_Adress 0x2D

//Values to write
#define Accelero_CTRL_REG1_A_Value_ToWrite 0x9F
#define Accelero_CTRL_REG4_A_Value_ToWrite 0x0

#define NumberOfLeds 8

#endif
