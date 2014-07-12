
#include "pio.h"

void PioSetPin(Pio* port, unsigned char pin, unsigned char state){
	if(state)
		port->PIO_SODR = 1 << pin;
	else
		port->PIO_CODR = 1 << pin;
}

/*
 * active
 * 
 * 0->Disable
 * 1->Enable
 */
void PioConfigMultSetPin(Pio* port, unsigned int pins, unsigned char active){
  if(active)
    port->PIO_OWER = pins;
  else
    port->PIO_OWDR = pins;
}

/*
 * source
 * 
 * 'A'->Peripheral A
 * 'B'->Peripheral B
 * 'P'->PIO
 * 
 * 
 * direction
 * 
 * 'I'->Input
 * 'O'->Otput
 * 'B'->Input and Output
 * 
 * 
 * pull_up
 * 
 * 0->Disable
 * 1->Enable
 */
void PioConfigMult(Pio* port, unsigned int pins, char source, char direction, unsigned char pull_up){
  if(source == 'A' || source == 'B'){
    port->PIO_PDR = pins;
    if(source == 'A')
      port->PIO_ABSR = port->PIO_ABSR & ~pins;
    else
      port->PIO_ABSR = port->PIO_ABSR | pins;
  }
  else if(source == 'P')
    port->PIO_PER = pins;
  
  if(direction == 'I' || direction == 'O'){
    port->PIO_MDDR = pins;
    if(direction == 'I')
      port->PIO_ODR = pins;
    else
      port->PIO_OER = pins;
  }
  else if(direction == 'B'){
    port->PIO_MDER = pins;
    port->PIO_OER = pins;
  }
  
  if(pull_up && (direction == 'I' || direction == 'B'))
	port->PIO_PUER = pins;
  else
	port->PIO_PUDR = pins;
}

/*
 * mode
 * 
 * 'G'->Glitch
 * 'D'->Debouncing
 * '0'->Disable
 * 
 * 
 * pulse_time in microseconds from 60us to 999425us
 */
void PioConfigMultGlitchDebouncing(Pio* port, unsigned int pins, char mode, unsigned int pulse_time){
  if(mode == 'D'){
    port->PIO_DIFSR = pins;
    if(pulse_time > 60 && pulse_time < 999425)
      port->PIO_SCDR = pulse_time/(2000000/SLOW_CLOCK)-1;
  }
  else if(mode == 'G')
    port->PIO_SCIFSR = pins;
  if(mode == 'D' || mode == 'G')
    port->PIO_IFER = pins;
  else if(mode == '0')
    port->PIO_IFDR = pins;
}

/*
 * event_detector
 * 
 * 'R'->Rising Edge Detector
 * 'F'->Falling Edge Detector
 * 'H'->High Level Detector
 * 'L'->Low Level Detector
 * 'E'->Edge Detector
 * 'D'->Disable
 */
void PioConfigMultInt(Pio* port, unsigned int pins, char event_detector){
  if(event_detector == 'R' || event_detector == 'H')
    port->PIO_REHLSR = pins;
  else if(event_detector == 'F' || event_detector == 'L')
    port->PIO_FELLSR = pins;
  if(event_detector == 'H' || event_detector == 'L')
    port->PIO_LSR = pins;
  else if(event_detector == 'R' || event_detector == 'F')
    port->PIO_ESR = pins;
  if(event_detector == 'R' || event_detector == 'F' || event_detector == 'H' || event_detector == 'L')
    port->PIO_AIMER = pins;
  else if(event_detector == 'E')
    port->PIO_AIMDR = pins;
  if(event_detector == 'R' || event_detector == 'F' || event_detector == 'H' || event_detector == 'L' || event_detector == 'E')
    port->PIO_IER = pins;
  else if(event_detector == 'D')
    port->PIO_IDR = pins;
}
