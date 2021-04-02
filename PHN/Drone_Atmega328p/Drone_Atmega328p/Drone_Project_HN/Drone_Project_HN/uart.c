/*
 * uart.c
 *
 * Created: 2021-01-07 오후 10:34:50
 *  Author: phn15
 */ 
#define F_CPU 16000000UL
#include "uart.h"

#define sbi(PORTX, BitX) (PORTX |= (1<<BitX))
#define cbi(PORTX, BitX) (PORTX &= ~(1<<BitX))

#define UART_BUFLEN 10

void UART_INIT(void){
	sbi(UCSR0A, U2X0); // U2X0 = 1 --> Baudrate 9600 = 207
	
	UBRR0H = 0x00;
	UBRR0L = 207;   // Baudrate 9600
	
	UCSR0C |= 0x06; // 1stop bit, 8bit data
	
	sbi(UCSR0B, RXEN0);  // enable receiver and transmitter
	sbi(UCSR0B, TXEN0);
}

unsigned char UART_receive(void)
{
	while(!(UCSR0A & (1<<RXC0))); // wait for data to be received
	return UDR0; // get and return received data from buffer
}

void UART_tranmit( char data)
{
	while(!(UCSR0A & (1<<UDRE0))); // wait for empty transmit buffer
	UDR0 = data; // put data into buffer, sends the data
}

void UART_string_transmit(char *string)
{
	while(*string != '\0')
	{
		UART_tranmit( *string );
		string++;
	}
}

void UART_PRINT(char *name, long val)
{
	char debug_buffer[UART_BUFLEN] = {'\0'};

	UART_string_transmit(name);
	UART_string_transmit(" = ");

	ltoa((val), debug_buffer, UART_BUFLEN);
	UART_string_transmit(debug_buffer);
	UART_string_transmit("\n");
}

int usartTxChar(char ch, FILE *fp) {  // for printf
	while (!(UCSR0A & (1 << UDRE0)));

	UDR0 = ch;

	return 0;
}