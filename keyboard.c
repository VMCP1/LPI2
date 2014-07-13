 
#include "pio.h"
#include "keyboard.h"

void KeyboardConfig(){
  PioConfig(PORTA, 15, 'P', 'I', 1);
  PioConfig(PORTB, 26, 'P', 'I', 1);
  PioConfigMult(PORTD, 0x00000209, 'P', 'I', 1);
  
  //PioConfigGlitchDebouncing(PORTA, 15, 'D', 50000);
  //PioConfigGlitchDebouncing(PORTB, 26, 'D', 50000);
  //PioConfigMultGlitchDebouncing(PORTD, 0x00000209, 'D', 50000);
}

/*
 * Return
 * 
 * 'U'->Up
 * 'D'->Down
 * 'L'->Left
 * 'R'->Right
 * 'O'->Ok
 * 'Z'->No Key Pressed
 */
char KeyboardGetKey(){
  if(!PioGetPin(PORTB, 26))
    return 'U';
  else if(!PioGetPin(PORTA, 15))
    return 'D';
  else if(!PioGetPin(PORTD, 1))
    return 'L';
  else if(!PioGetPin(PORTD, 3))
    return 'R';
  else if(!PioGetPin(PORTD, 9))
    return 'O';
  else
    return 'Z';
}
