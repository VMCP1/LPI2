#define SERIE_C

#include "uart.h"
#include "serie.h"

static volatile unsigned char ostart = 0; // transmission buffer start index
static unsigned char oend = 0; // transmission buffer end index
static unsigned char outbuf[OLEN]; // storage for transmission 

static unsigned char istart = 0; // receiving buffer start index
static volatile unsigned char iend = 0; // receiving buffer end index
static volatile unsigned char inbuf[ILEN];

volatile SerieFlag serie_flags;

/* Function to initialize the serial port and the UART baudrate.
*------------------------------------------------------------------------------*/
void SerieInitialize(unsigned int baude_rate){
  UartConfig(baude_rate, 'N');
  UartConfigInt('R', 1);
  UartEnable(1, 1);
  UartEnable(0, 1);
}

// Serial Interrupt Service Routine
//----- Received data interrupt. -----
void UART_Handler_RXRDY(void){
  unsigned char c = UartGetByte(); // read character

  if(istart + ILEN != iend){
    inbuf[iend++ & (ILEN-1)] = c; // put character into buffer
    serie_flags.rcvempty = 0;
  }
}

static void wait(unsigned int ul_time){
	while(ul_time--){
		__asm__ __volatile__("nop\n\t");
	}
}

//----- Transmitted data interrupt. -----
void UART_Handler_TXRDY(void){
  if(ostart != oend){ // if characters in buffer and
    UartPutByte(outbuf[ostart++ & (OLEN-1)]); // transmit character
    serie_flags.sendfull = 0; // clear 'serie_flags.sendfull' flag
  }
  else{ // if all characters transmitted
    serie_flags.sendactive = 0; // clear 'serie_flags.sendactive'
    UartConfigInt('T', 0); // Disable Interrupt
  }
    //while(!UartPutFlagTxReady());
    //UART->UART_CR.RSTTX = 1;
    //while(1);
}

/* putchar: write a character to UART or transmission buffer */
void SeriePutByte(char c){
  while(serie_flags.sendfull); // wait until there is space in buffer
  if(!serie_flags.sendactive){ // if transmitter not active:
    serie_flags.sendactive = 1; // transfer first character direct
    UartPutByte((unsigned char)c); // to UART to start transmission
    UartConfigInt('T', 1); // Enable Interrupt
  }
  else{
    UartEnable(0, 0); // disable serial interrupts during buffer update
    outbuf[oend++ & (OLEN-1)] = c; // put char to transmission buffer
    if(((oend ^ ostart) & (OLEN-1)) == 0)
      serie_flags.sendfull = 1; // set flag if buffer is full
    UartEnable(0, 1); // enable serial interrupts again
  }
}

/*--------------------------------------------------------------------------------
* Replacement routine for the standard library _getkey routine.
* The getchar and gets functions uses _getkey to read a character.
*------------------------------------------------------------------------------*/
char SerieGetByte(void){
  unsigned char c;
  
  while(iend == istart);
  UartEnable(1, 0); // disable serial interrupts during buffer update
  c = inbuf[istart++ & (ILEN-1)];
  UartEnable(1, 1); // enable serial interrupts again
  
  return c;
}

// Print string
void SeriePutString(const char* string){
  while(*string != '\0')
    SeriePutByte(*string++);
}
