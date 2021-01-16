/*
 * uart.h
 *
 * Created: 2021-01-07 오후 10:35:11
 *  Author: phn15
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void UART_INIT(void);
unsigned char UART_receive(void);
void UART_tranmit( char data);
void UART_string_transmit(char *string);
void UART_PRINT(char *name, long val);
int usartTxChar(char ch, FILE *fp);  // for printf

#endif /* UART_H_ */