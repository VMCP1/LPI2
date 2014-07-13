 
#include "esterio.h"

// Subcarrier 38kHz
static signed F38KHz[] = {
  1000,
  707,
  0,
  -707,
  -1000,
  -707,
  0,
  707
}

// Pilot Tone of 19 KHz
static signed F19KHz[] = {
  1000,
  0,
  -1000,
  0,
  1000,
  0,
  -1000,
  0
}

unsigned int ExecuteEsterio(int channel_l, int channel_r){
  int LpR, LmR, signal, LmR38kHz;
  static unsigned char time = 0;
  
  // Left Channel + Right Channel
  LpR = L+R;
  
  // Left Channel - Right Channel
  LmR = L-R;
  
  LmR38kHz = LmR * F38kHz[time & 0x07];
  
  signal = LmR38kHz + F19kHz[time++ & 0x07] + LpR;
  
  return signal;
}
