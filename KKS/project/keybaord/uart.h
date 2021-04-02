/*
 * UART.h
 *
 * Created: 2020-11-07 오전 3:52:03
 *  Author: KKS
 */ 


#ifndef UART_H_
#define UART_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void uart_init(void);
unsigned char uart_receive(void);
void uart_tranmit( char data);
void uart_string_transmit(char *string);
void uart_print(char *name, long val);
int usartTxChar(char ch, FILE *fp);  // for printf

#endif /* UART_H_ */