/*
 * UART.c
 *
 * Created: 2020-12-23 오전 2:27:31
 *  Author: 82107
 */ 
#include "essential.h"
#define UART_BUFLEN 10

void uart_init(void)
{
	sbi(UCSR0A, U2X0);
	sbi(UCSR0B, RXEN0);
	sbi(UCSR0B, TXEN0);
	UBRR0H = 0;
	UBRR0L = 207; //Baud Rate 9600
}

void uart_transmit(uint8_t data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

uint8_t uart_receive(void)
{
	while(!(UCSR0A & (1<< RXC0)));
	
	return UDR0;
}

void uart_string_transmit(uint8_t string[])
{
	while(1)
	{
		if(*string != '\0'){
			uart_transmit(*string);
			string++;
		}
		else break;
		
	}
}

void uart_print(char *name, long val)
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