#include "../ATSAM3X8E/include/startup_sam3xa.h"
#include "uart.h"
#include "pio.h"

unsigned char UartFlagsError(){
  unsigned flags = (UART->UART_SR.PARE << 2) + (UART->UART_SR.FRAME << 1) + UART->UART_SR.OVRE;
  UART->UART_CR.RSTSTA = 1;
  return flags;
}

/*
 * direction
 * 
 * 0->TX
 * 1->RX
 * 
 * 
 *  enable
 * 
 * 0->Disable
 * 1->Enable
 */
void UartEnable(unsigned char direction, unsigned char enable){
  if(direction && enable){
    PioConfig(PORTA, 8, 'A', 'I', 1);
    UART->UART_CR.RXEN = 1;
  }
  else if(direction && !enable)
    UART->UART_CR.RXDIS = 1;
  else if(!direction && enable){
    PioConfig(PORTA, 9, 'A', 'O', 0);
    UART->UART_CR.TXEN = 1;
  }
  else if(!direction && !enable)
    UART->UART_CR.TXDIS = 1;
}

/*
 * parity
 * 
 * 'E'->Evan
 * 'O'->Odd
 * 'N'->No parity
 */
void UartConfig(unsigned int baude_rate, char parity){
  if(baude_rate > 0 && baude_rate < 5250001)
    UART->UART_BRGR = MASTER_CLOCK/(16*baude_rate);
  
  switch(parity){
    case 'E':
      UART->UART_MR.PAR = UART_MR_PAR_EVEN;
      break;
    case 'O':
      UART->UART_MR.PAR = UART_MR_PAR_ODD;
      break;
    case 'N':
      UART->UART_MR.PAR = UART_MR_PAR_NO;
  }
}

/*
 * interrupt
 * 
 * 'R'->Rx Ready Interrupt
 * 'T'->Tx Ready Interrupt
 * 'O'->Over Read Error Interrupt
 * 'F'->Frame Error Interrupt
 * 'P'->Pare Error Interrupt
 * 'E'->Tx Empty Interrupt
 * 
 * 
 * enable
 * 
 * 0->Disable
 * 1->Enable
 */
void UartConfigInt(char interrupt, unsigned char enable){
  switch(interrupt){
    case 'R':
      if(enable)
	UART->UART_IER.RXRDY = 1;
      else
	UART->UART_IDR.RXRDY = 1;
      break;
    case 'T':
      if(enable)
	UART->UART_IER.TXRDY = 1;
      else
	UART->UART_IDR.TXRDY = 1;
      break;
    case 'O':
      if(enable)
	UART->UART_IER.OVRE = 1;
      else
	UART->UART_IDR.OVRE = 1;
      break;
    case 'F':
      if(enable)
	UART->UART_IER.FRAME = 1;
      else
	UART->UART_IDR.FRAME = 1;
      break;
    case 'P':
      if(enable)
	UART->UART_IER.PARE = 1;
      else
	UART->UART_IDR.PARE = 1;
      break;
    case 'E':
      if(enable)
	UART->UART_IER.TXEMPTY = 1;
      else
	UART->UART_IDR.TXEMPTY = 1;
  }
}

void UART_Handler(void){
    if(UART->UART_SR.RXRDY)
      UART_Handler_RXRDY();
    if(UART->UART_SR.TXRDY)
      UART_Handler_TXRDY();
    if(UART->UART_SR.OVRE)
      UART_Handler_OVRE();
    if(UART->UART_SR.FRAME)
      UART_Handler_FRAME();
    if(UART->UART_SR.PARE)
      UART_Handler_PARE();
    if(UART->UART_SR.TXEMPTY)
      UART_Handler_TXEMPTY();
}
