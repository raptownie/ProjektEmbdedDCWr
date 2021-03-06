#ifndef CONFIGHeader
#define CONFIGHeader

#ifndef DeviceHeader
#define DeviceHeader
#include "stm32f3xx.h"                  // Device header
#endif

#define TimeToTurnOnOffDevice_ms 2500
#define UartMaxDataSizeToRecive 40
#define UartMaxDataSizeToSend 100

//Co ile bedzie generwoany impuls przerwania - obsluga standby
#define TIM7_Prescaler                 9999        // 72Mhz/(TIM7_Prescaler+1) - ilosc impulsow na 1s
#define TIM7_AutoReloadRegisterValue   720         // co ile impuls?w TIM7 ma generowac przerwanie 
#define TIM7To_ms                       (1000*TIM7_AutoReloadRegisterValue/(ClockHZ/(TIM7_Prescaler+1)))   // takaby makro TimeToTurnOnOffDevice_ms dzialalo niezaleznie od parametrow licznika TIM7

//Co ile beda generwoane nowe wartosci gyroskopu/accelero
#define TIM6_Prescaler                 9999        // 72Mhz/(TIM6_Prescaler+1) - ilosc impulsow na 1s
#define TIM6_AutoReloadRegisterValue   144         // co ile impuls?w TIM7 ma generowac przerwanie 

//CC1 - co ile impulsow bd uruchamiana funkcja tworzaca dane dla UARTa
//AutoReloadRegister - co ile bedzie wystepowac przerwanie wysylajace dane przez UARTA
#define TIM1_Prescaler                 9999       // 72Mhz/(TIM1_Prescaler+1) - ilosc impulsow na 1s
#define TIM1_AutoReloadRegisterValue   3600        // co ile impuls?w TIM1 ma generowac przerwanie
#define TIM1_CCR1_value                2000       //co ile impulsow generowane jest przerwanie z kanalu pierwszego TIM1 

//licznik do odswiezania displaya
#define TIM8_Prescaler                 9999       // 72Mhz/(TIM8_Prescaler+1) - ilosc impulsow na 1s
#define TIM8_AutoReloadRegisterValue   72     // co ile impuls?w TIM1 ma generowac przerwanie

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

//MainStatePerform ButtonStatePerform
#define DebounceValue 10
#define MainStateAfterWakeUp GyroState

//LedControl

#define LedStructName      tLedStatus

#define NumberOfLeds 8

/*       
                    [7] LD10(PE13) N
          [6] LD9(PE12) NW          [5] LD8(PE14) NE
 [4] LD7(PE11) W                             [3] LD6(PE15) E
          [1] LD5(PE10) SW          [1] LD4(PE8) SE
                    [0] LD3(PE9) S
*/

#define LD3_S              0
#define LD3_S_ODR          GPIO_ODR_9
#define LD4_SE             1
#define LD4_SE_ODR         GPIO_ODR_8
#define LD5_SW             2
#define LD5_SW_ODR         GPIO_ODR_10
#define LD6_E              3
#define LD6_E_ODR          GPIO_ODR_15
#define LD7_W              4
#define LD7_W_ODR          GPIO_ODR_11
#define LD8_NE             5
#define LD8_NE_ODR         GPIO_ODR_14
#define LD9_NW             6
#define LD9_NW_ODR         GPIO_ODR_12
#define LD10_N             7  
#define LD10_N_ODR         GPIO_ODR_13 

#define GPIOx_ODR    GPIOE->ODR

#define TurnOnOffLedSequenceDelay 300

#define TurnOffLedSequenceDate {LD3_S, LD5_SW, LD7_W, LD9_NW, LD10_N, LD8_NE, LD6_E, LD4_SE}
#define TurnOnLedSequenceDate {LD3_S, LD4_SE, LD6_E, LD8_NE, LD10_N, LD9_NW, LD7_W, LD5_SW}

#endif
