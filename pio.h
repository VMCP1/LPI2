
#ifndef PIO_H
#define PIO_H

#define PORTA ((Pio*)0x400E0E00)
#define PORTB ((Pio*)0x400E1000)
#define PORTC ((Pio*)0x400E1200)
#define PORTD ((Pio*)0x400E1400)

#define KEY 0x50494
typedef struct{
  volatile unsigned int WPEN:1;   // Write Protect Enable
  volatile unsigned int Reserved1:7;
  volatile unsigned int WPKEY:24; // Write Protect KEY (KEY = 0x50494F = "PIO")
}PioWpmr;

typedef struct{
  volatile unsigned int WPVS:1;    // Write Protect Violation Status
  volatile unsigned int Reserved1:7;
  volatile unsigned int WPVSRC:16; // Write Protect Violation Source
}PioWpsr;

/* Pio hardware registers */
typedef struct {
  volatile unsigned int PIO_PER;          /*(Pio Offset: 0x0000) PIO Enable Register */
  volatile unsigned int PIO_PDR;          /*(Pio Offset: 0x0004) PIO Disable Register */
  volatile const unsigned int PIO_PSR;    /*(Pio Offset: 0x0008) PIO Status Register */
  volatile const unsigned int Reserved1[1];
  volatile unsigned int PIO_OER;          /*(Pio Offset: 0x0010) Output Enable Register */
  volatile unsigned int PIO_ODR;          /*(Pio Offset: 0x0014) Output Disable Register */
  volatile const unsigned int PIO_OSR;    /*(Pio Offset: 0x0018) Output Status Register */
  volatile const unsigned int Reserved2[1];
  volatile unsigned int PIO_IFER;         /*(Pio Offset: 0x0020) Glitch Input Filter Enable Register */
  volatile unsigned int PIO_IFDR;         /*(Pio Offset: 0x0024) Glitch Input Filter Disable Register */
  volatile const unsigned int PIO_IFSR;   /*(Pio Offset: 0x0028) Glitch Input Filter Status Register */
  volatile const unsigned int Reserved3[1];
  volatile unsigned int PIO_SODR;         /*(Pio Offset: 0x0030) Set Output Data Register */
  volatile unsigned int PIO_CODR;         /*(Pio Offset: 0x0034) Clear Output Data Register */
  volatile unsigned int PIO_ODSR;         /*(Pio Offset: 0x0038) Output Data Status Register */
  volatile const unsigned int PIO_PDSR;   /*(Pio Offset: 0x003C) Pin Data Status Register */
  volatile unsigned int PIO_IER;          /*(Pio Offset: 0x0040) Interrupt Enable Register */
  volatile unsigned int PIO_IDR;          /*(Pio Offset: 0x0044) Interrupt Disable Register */
  volatile const unsigned int PIO_IMR;    /*(Pio Offset: 0x0048) Interrupt Mask Register */
  volatile const unsigned int PIO_ISR;    /*(Pio Offset: 0x004C) Interrupt Status Register */
  volatile unsigned int PIO_MDER;         /*(Pio Offset: 0x0050) Multi-driver Enable Register */
  volatile unsigned int PIO_MDDR;         /*(Pio Offset: 0x0054) Multi-driver Disable Register */
  volatile const unsigned int PIO_MDSR;   /*(Pio Offset: 0x0058) Multi-driver Status Register */
  volatile const unsigned int Reserved4[1];
  volatile unsigned int PIO_PUDR;         /*(Pio Offset: 0x0060) Pull-up Disable Register */
  volatile unsigned int PIO_PUER;         /*(Pio Offset: 0x0064) Pull-up Enable Register */
  volatile const unsigned int PIO_PUSR;   /*(Pio Offset: 0x0068) Pad Pull-up Status Register */
  volatile const unsigned int Reserved5[1];
  volatile unsigned int PIO_ABSR;         /*(Pio Offset: 0x0070) Peripheral AB Select Register */
  volatile const unsigned int Reserved6[3];
  volatile unsigned int PIO_SCIFSR;       /*(Pio Offset: 0x0080) System Clock Glitch Input Filter Select Register */
  volatile unsigned int PIO_DIFSR;        /*(Pio Offset: 0x0084) Debouncing Input Filter Select Register */
  volatile const unsigned int PIO_IFDGSR; /*(Pio Offset: 0x0088) Glitch or Debouncing Input Filter Clock Selection Status Register */
  volatile unsigned int PIO_SCDR;         /*(Pio Offset: 0x008C) Slow Clock Divider Debouncing Register */
  volatile const unsigned int Reserved7[4];
  volatile unsigned int PIO_OWER;         /*(Pio Offset: 0x00A0) Output Write Enable */
  volatile unsigned int PIO_OWDR;         /*(Pio Offset: 0x00A4) Output Write Disable */
  volatile const unsigned int PIO_OWSR;   /*(Pio Offset: 0x00A8) Output Write Status Register */
  volatile const unsigned int Reserved8[1];
  volatile unsigned int PIO_AIMER;        /*(Pio Offset: 0x00B0) Additional Interrupt Modes Enable Register */
  volatile unsigned int PIO_AIMDR;        /*(Pio Offset: 0x00B4) Additional Interrupt Modes Disables Register */
  volatile const unsigned int PIO_AIMMR;  /*(Pio Offset: 0x00B8) Additional Interrupt Modes Mask Register */
  volatile const unsigned int Reserved9[1];
  volatile unsigned int PIO_ESR;          /*(Pio Offset: 0x00C0) Edge Select Register */
  volatile unsigned int PIO_LSR;          /*(Pio Offset: 0x00C4) Level Select Register */
  volatile const unsigned int PIO_ELSR;   /*(Pio Offset: 0x00C8) Edge/Level Status Register */
  volatile const unsigned int Reserved10[1];
  volatile unsigned int PIO_FELLSR;       /*(Pio Offset: 0x00D0) Falling Edge/Low Level Select Register */
  volatile unsigned int PIO_REHLSR;       /*(Pio Offset: 0x00D4) Rising Edge/ High Level Select Register */
  volatile const unsigned int PIO_FRLHSR; /*(Pio Offset: 0x00D8) Fall/Rise - Low/High Status Register */
  volatile const unsigned int Reserved11[1];
  volatile const unsigned int PIO_LOCKSR; /*(Pio Offset: 0x00E0) Lock Status */
  volatile unsigned int PIO_WPMR;         /*(Pio Offset: 0x00E4) Write Protect Mode Register */
  volatile const unsigned int PIO_WPSR;   /*(Pio Offset: 0x00E8) Write Protect Status Register */
} Pio;


void PioSetPin(Pio* port, unsigned char pin, unsigned char state);

#define PioGetPin(port, pin) ((port->PIO_PDSR & (1 << pin)) >> pin)

/*
 * active
 * 
 * 0->Disable
 * 1->Enable
 */
void PioConfigMultSetPin(Pio* port, unsigned int pins, unsigned char active);

#define PioSetMultPin(port, data) (port->PIO_ODSR = data)

#define PioGetMultPin(port) (port->PIO_PDSR)

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
#define PioConfig(port, pin, source, direction, pull_up) PioConfigMult(port, 1 << pin, source, direction, pull_up)
void PioConfigMult(Pio* port, unsigned int pins, char source, char direction, unsigned char pull_up);

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
#define PioConfigGlitchDebouncing(port, pin, mode, pulse_time) PioConfigMultGlitchDebouncing(port, 1 << pin, mode, pulse_time)
void PioConfigMultGlitchDebouncing(Pio* port, unsigned int pins, char mode, unsigned int pulse_time);

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
#define PioConfigPioInt(port, pin, event_detector) PioConfigMultPioInt(port, 1 << pin, event_detector)
void PioConfigMultPioInt(Pio* port, unsigned int pins, char event_detector);

#endif
