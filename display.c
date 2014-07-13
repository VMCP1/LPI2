
#include "display.h"
#include "pio.h"

static void wait(unsigned int ul_time){
  while(ul_time--){
    __asm__ __volatile__("nop\n\t");
  }
}

void SendLcd(unsigned char byte){
  PioSetPin(PORTC, 14, (byte & 0x10) >> 4);
  PioSetPin(PORTC, 16, (byte & 0x20) >> 5);
  PioSetPin(PORTC, 18, (byte & 0x40) >> 6);
  PioSetPin(PORTA, 20, (byte & 0x80) >> 7);
  //wait(1000);
  
  // Set LCD_E Pin
  PioSetPin(PORTC, 12, 1);
  // Clear LCD_E Pin;
  wait(1000);
  PioSetPin(PORTC, 12, 0);
  
  PioSetPin(PORTC, 14, (byte & 0x01) >> 0);
  PioSetPin(PORTC, 16, (byte & 0x02) >> 1);
  PioSetPin(PORTC, 18, (byte & 0x04) >> 2);
  PioSetPin(PORTA, 20, (byte & 0x08) >> 3);
  //wait(1000);
  
  // Set LCD_E Pin
  PioSetPin(PORTC, 12, 1);
  // Clear LCD_E Pin;
  wait(1000);
  PioSetPin(PORTC, 12, 0);
}

void DisplayInit(){
  PioConfig(PORTA, 20, 'P', 'O', 0);
  PioConfig(PORTB, 14, 'P', 'O', 0);
  PioConfigMult(PORTC, 0x00055280, 'P', 'O', 0);
  
  wait(1000000);
  
  // RS line to 0
  PioSetPin(PORTB, 14, 0);
  
  // Function set
  SendLcd(0x28);
  
  // Display on/off
  SendLcd(0x0c);
  
  // Clear display
  SendLcd(0x01);
  
  // Entry mode set
  SendLcd(0x06);
}

void Display(char msg[], unsigned char line){
  unsigned char i;
  
  // RS line to 0
  PioSetPin(PORTB, 14, 0);
  
  if(!line){
    // Return Home
    SendLcd(0x02);
    wait(50000);
  }
  else
    // Return Home
    SendLcd(0xbf);
  
  // RS line to 1
  PioSetPin(PORTB, 14, 1);
  
  // Send First Line
  for(i = 0; i < 16; i++)
    SendLcd(msg[i]);
}
