/*
 * UART.c
 *
 * Created: 2020-11-07 오전 3:50:31
 *  Author: KKS
 */ 
#define F_CPU 16000000UL
//#define F_CPU 8000000UL
#include "uart.h"

#define sbi(PORTX, BitX) (PORTX |= (1<<BitX))
#define cbi(PORTX, BitX) (PORTX &= ~(1<<BitX))

#define UART_BUFLEN 10

void uart_init(void){
	
	UBRR1H = 0x00;
	UBRR1L = 103;   // 9600BPS
	
	UCSR1C |= 0x06; // 1stop bit, 8bit data
	
	sbi(UCSR1B, RXEN1);  // enable receiver and transmitter
	sbi(UCSR1B, TXEN1);
}

unsigned char uart_receive(void)
{
	while(!(UCSR1A & (1<<RXC1))); // wait for data to be received
	return UDR1; // get and return received data from buffer
}

void uart_tranmit( char data)
{
	while(!(UCSR1A & (1<<UDRE1))); // wait for empty transmit buffer
	UDR1 = data; // put data into buffer, sends the data
}

void uart_string_transmit(char *string)
{
	while(*string != '\0')
	{
		uart_tranmit( *string );
		string++;
	}
}

void uart_print(char *name, long val)
{
	char debug_buffer[UART_BUFLEN] = {'\0'};

	uart_string_transmit(name);
	uart_string_transmit(" = ");

	ltoa((val), debug_buffer, UART_BUFLEN);
	uart_string_transmit(debug_buffer);
	uart_string_transmit("\n");
}

int usartTxChar(char ch, FILE *fp) {  // for printf
	while (!(UCSR1A & (1 << UDRE1)));

	UDR1 = ch;
	
	return 0;
}


