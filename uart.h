
#ifndef UART_H
#define UART_H

#define UART ((Uart*)0x400E0800)

typedef struct{
  unsigned int Reserved1:2;
  unsigned int RSTRX:1;  // Reset Receiver
  unsigned int RSTTX:1;  // Reset Transmitter
  unsigned int RXEN:1;   // Receiver Enable
  unsigned int RXDIS:1;  // Receiver Disable
  unsigned int TXEN:1;   // Transmitter Enable
  unsigned int TXDIS:1;  // Transmitter Disable
  unsigned int RSTSTA:1; // Reset Status Bit
}UartCr;

// PAR
#define UART_MR_PAR_EVEN 0  // Even parity
#define UART_MR_PAR_ODD 1   // Odd parity
#define UART_MR_PAR_SPACE 2 // Space: parity forced to 0
#define UART_MR_PAR_MARK 3  // Mark: parity forced to 1
#define UART_MR_PAR_NO 4    // No parity
// CHMODE
#define UART_MR_CHMODE_NORMAL 0          // Normal Mode
#define UART_MR_CHMODE_AUTOMATIC 1       // Automatic Echo
#define UART_MR_CHMODE_LOCAL_LOOPBACK 2  // Local Loopback
#define UART_MR_CHMODE_REMOTE_LOOPBACK 3 // Remote Loopback
typedef struct{
  unsigned int Reserved1:9;
  unsigned int PAR:3;   // Parity Type
  unsigned int Reserved2:2;
  unsigned int CHMODE:2; // Channel Mode
}UartMr;

typedef struct{
  unsigned int RXRDY:1;   // Enable RXRDY Interrupt
  unsigned int TXRDY:1;   // Enable TXRDY Interrupt
  unsigned int Reserved1:1;
  unsigned int ENDRX:1;   // Enable End of Receive Transfer Interrupt
  unsigned int ENDTX:1;   // Enable End of Transmit Interrupt
  unsigned int OVRE:1;    // Enable Overrun Error Interrupt
  unsigned int FRAME:1;   // Enable Framing Error Interrupt
  unsigned int PARE:1;    // Enable Parity Error Interrupt
  unsigned int Reserved2:1;
  unsigned int TXEMPTY:1; // Enable TXEMPTY Interrupt
  unsigned int Reserved3:1;
  unsigned int TXBUFF:1;  // Enable Buffer Empty Interrupt
  unsigned int RXBUFF:1;  // Enable Buffer Full Interrupt
}UartIer;

typedef struct{
  unsigned int RXRDY:1;   // Disable RXRDY Interrupt
  unsigned int TXRDY:1;   // Disable TXRDY Interrupt
  unsigned int Reserved1:1;
  unsigned int ENDRX:1;   // Disable End of Receive Transfer Interrupt
  unsigned int ENDTX:1;   // Disable End of Transmit Interrupt
  unsigned int OVRE:1;    // Disable Overrun Error Interrupt
  unsigned int FRAME:1;   // Disable Framing Error Interrupt
  unsigned int PARE:1;    // Disable Parity Error Interrupt
  unsigned int Reserved2:1;
  unsigned int TXEMPTY:1; // Disable TXEMPTY Interrupt
  unsigned int Reserved3:1;
  unsigned int TXBUFF:1;  // Disable Buffer Empty Interrupt
  unsigned int RXBUFF:1;  // Disable Buffer Full Interrupt
}UartIdr;

typedef struct{
  const unsigned int RXRDY:1;   // Mask RXRDY Interrupt
  const unsigned int TXRDY:1;   // Mask TXRDY Interrupt
  const unsigned int Reserved1:1;
  const unsigned int ENDRX:1;   // Mask End of Receive Transfer Interrupt
  const unsigned int ENDTX:1;   // Mask End of Transmit Interrupt
  const unsigned int OVRE:1;    // Mask Overrun Error Interrupt
  const unsigned int FRAME:1;   // Mask Framing Error Interrupt
  const unsigned int PARE:1;    // Mask Parity Error Interrupt
  const unsigned int Reserved2:1;
  const unsigned int TXEMPTY:1; // Mask TXEMPTY Interrupt
  const unsigned int Reserved3:1;
  const unsigned int TXBUFF:1;  // Mask Buffer Empty Interrupt
  const unsigned int RXBUFF:1;  // Mask Buffer Full Interrupt
}UartImr;

typedef struct{
  const unsigned int RXRDY:1;   // Receiver Ready
  const unsigned int TXRDY:1;   // Transmitter Ready
  const unsigned int Reserved1:1;
  const unsigned int ENDRX:1;   // End of Receive Transfer
  const unsigned int ENDTX:1;   // End of Transmit Transfer
  const unsigned int OVRE:1;    // Overrun Error
  const unsigned int FRAME:1;   // Framing Error
  const unsigned int PARE:1;    // Parity Error
  const unsigned int Reserved2:1;
  const unsigned int TXEMPTY:1; // Transmitter Empty
  const unsigned int Reserved3:1;
  const unsigned int TXBUFF:1;  // Transmission Buffer Empty
  const unsigned int RXBUFF:1;  // Receive Buffer Full
}UartSr;

/* Uart hardware registers */
typedef struct {
  UartCr UART_CR;                       /* (Uart Offset: 0x0000) Control Register */
  UartMr UART_MR;                       /* (Uart Offset: 0x0004) Mode Register */
  UartIer UART_IER;                     /* (Uart Offset: 0x0008) Interrupt Enable Register */
  UartIdr UART_IDR;                     /* (Uart Offset: 0x000C) Interrupt Disable Register */
  UartImr UART_IMR;                     /* (Uart Offset: 0x0010) Interrupt Mask Register */
  volatile UartSr UART_SR;              /* (Uart Offset: 0x0014) Status Register */
  volatile const unsigned int UART_RHR; /* (Uart Offset: 0x0018) Receive Holding Register */
  unsigned int UART_THR;                /* (Uart Offset: 0x001C) Transmit Holding Register */
  unsigned int UART_BRGR;               /* (Uart Offset: 0x0020) Baud Rate Generator Register */
}Uart;


#define UartFlagRxReady() UART->UART_SR.RXRDY
#define UartGetByte() UART->UART_RHR

#define UartPutFlagTxReady() UART->UART_SR.TXRDY
#define UartPutFlagTxEmpty() UART->UART_SR.TXEMPTY
#define UartPutByte(byte) (UART->UART_THR=byte)

/*
 * return
 * 
 * bit0->Pare Error Flag
 * bit1->Frame Error Flag
 * bit2->Over Read Error Flag
 */
unsigned char UartFlagsError();

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
void UartEnable(unsigned char direction, unsigned char enable);

/*
 * parity
 * 
 * 'E'->Evan
 * 'O'->Odd
 * 'N'->No parity
 */
void UartConfig(unsigned int baude_rate, char parity);

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
void UartConfigInt(char interrupt, unsigned char enable);

/*
 * Uart Interrupt Vector
 */
void UART_Handler_RXRDY(void);
void UART_Handler_TXRDY(void);
void UART_Handler_OVRE(void);
void UART_Handler_FRAME(void);
void UART_Handler_PARE(void);
void UART_Handler_TXEMPTY(void);

#endif
