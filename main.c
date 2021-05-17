#include "headers/main.h"

 int main (void){
   
   UserSystemInit_SystemSetup();   
  
   while(1){  
        
      MainPerform_MainStatePerform();
      ButtonPerform_ButtonStatePerform();   
   }
}
 

 


