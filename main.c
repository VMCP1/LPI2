
#include "../ATSAM3X8E/include/sam3x8e.h"
#include "pio.h"
#include "serie.h"
#include "uart.h"

static void wait(unsigned int ul_time){
	while(ul_time--){
		__asm__ __volatile__("nop\n\t");
	}
}

int main(void){
	volatile unsigned int* pointer;
	char c = 'P';
	char string[] = "Paulo Z";


	/*
	* SAM System init: Initializes the PLL / clock.
	* Defined in CMSIS/ATMEL/sam3xa/source/system_sam3xa.c
	*/
	SystemInit();
	PioConfig(PORTB, 27, 'P', 'O', 0);
	//pointer = 0x400e0610;
	//*pointer = 0x00000100;
	pointer = 0xe000e100;
	*pointer = 0x00000100;
	//pointer = 0xe000e200;
	//*pointer = 0x00000100;
	SerieInitialize(115200);
	//UartConfigInt('T', 1);
	//pointer = 0xe000e200;
	//*pointer = 0x00000100;
	//pointer = 0x400E0814;

	while(1){
		wait(10000000);
		PioSetPin(PORTB, 27, 1);
		//if(!serie_flags.rcvempty)
		//  c = SerieGetByte();
		wait(10000000);
		//if((*pointer) & 0x00000200)
		//UART->UART_THR = 'A';
		//while(!UART->UART_SR.TXRDY);
		//UART->UART_THR = 'B';
		PioSetPin(PORTB, 27, 0);
//UART->UART_THR='A';
//while(!(*pointer & 0x00000002));
//UART->UART_THR='B';
//while(!(UART->UART_SR.TXRDY));
//while(1);
		SeriePutString(string);
	}
	
	return 0;
}
