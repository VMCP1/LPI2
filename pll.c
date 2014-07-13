
#include "pio.h"
#include "pll.h"

void PllConfig(unsigned int freq){
  PioConfig(PORTA, 15, 'P', 'O', 0); // DLEN
  PioConfig(PORTB, 26, 'P', 'O', 0); // CLB
  PioConfig(PORTD, 1, 'P', 'O', 0); // DATA
}

static void wait(unsigned int ul_time){
  while(ul_time--){
    __asm__ __volatile__("nop\n\t");
  }
}

void Puls(){
  PioSetPin(PORTB, 26, 1);
  wait(20);
  PioSetPin(PORTB, 26, 0);
  wait(20);
}

void PllStartTrama(){
  PioSetPin(PORTD, 1, 0);
  PioSetPin(PORTA, 15, 1);
  Puls();
}

void PllStopTrama(){
  PioSetPin(PORTD, 1, 0);
  PioSetPin(PORTA, 15, 0);
  Puls();
}

void PllSendBit(unsigned char bit){
  PioSetPin(PORTD, 1, bit);
  Puls();
}

void PllWord(char word ,unsigned int freq){
  unsigned char b15;
  
  if(word == 'A')
    b15 = 0; // bit15
  else if(word == 'B')
    b15 = 1; // bit15
  else
    return;
  
  PllStartTrama();
  
  PllSendBit(b15); // bit15
  PllSendBit((freq & 0x00004000) >> 14); // bit14
  PllSendBit((freq & 0x00002000) >> 13); // bit13
  PllSendBit((freq & 0x00001000) >> 12); // bit12
  PllSendBit((freq & 0x00000800) >> 11); // bit11
  PllSendBit((freq & 0x00000400) >> 10); // bit10
  PllSendBit((freq & 0x00000200) >> 9); // bit9
  PllSendBit((freq & 0x00000100) >> 8); // bit8
  PllSendBit((freq & 0x00000080) >> 7); // bit7
  PllSendBit((freq & 0x00000040) >> 6); // bit6
  PllSendBit((freq & 0x00000020) >> 5); // bit5
  PllSendBit((freq & 0x00000010) >> 4); // bit4
  PllSendBit((freq & 0x00000008) >> 3); // bit3
  PllSendBit((freq & 0x00000004) >> 2); // bit2
  PllSendBit((freq & 0x00000002) >> 1); // bit1
  PllSendBit((freq & 0x00000001) >> 0); // bit0
  
  PllStopTrama();
}

void PllSetFreq(unsigned int freq){
  unsigned char word_l, word_h, i;
  
  freq+=70000000;
  if(freq > 120000000)
    return;
  freq/=10000;
  
  word_l = freq & 0x000000ff;
  word_h = (freq & 0x0000ff00) >> 8;
  
  for(i=0; i<14; i++)
    Puls();
  
  PllWord('B', 0xdd05);
  PllWord('A', freq);
  
  for(i=0; i<7; i++){
    PllWord('B', 0xdd85);
    PllWord('A', freq);
  }
  
  PllWord('B', 0xc385);
  PllWord('A', freq);
}
