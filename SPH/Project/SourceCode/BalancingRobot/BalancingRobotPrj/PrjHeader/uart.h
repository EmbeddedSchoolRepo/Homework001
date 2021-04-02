/*
 * uart.h
 *
 * Created: 2020-11-07 오전 3:51:24
 *  Author: SON
 */ 


#ifndef UART_H_
#define UART_H_

#include "PrjHeader.h"

void UART_INIT(void);
unsigned char UART_receive(void);
void UART_tranmit( char data);
void UART_string_transmit(char *string);
void UART_PRINT(char *name, long val);
int usartTxChar(char ch, FILE *fp);  // for printf

#endif /* UART_H_ */