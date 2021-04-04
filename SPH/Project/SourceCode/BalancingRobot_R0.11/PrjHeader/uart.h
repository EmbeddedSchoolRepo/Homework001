/*
 * uart.h
 *
 * Created: 2020-11-07 오전 3:51:24
 *  Author: SON
 */ 


#ifndef UART_H_
#define UART_H_

#include "PrjHeader.h"

extern void UART_INIT(void);
extern unsigned char UART_receive(void);
extern void UART_tranmit( char data);
extern void UART_string_transmit(char *string);
extern void UART_PRINT(char *name, long val);
extern int usartTxChar(char ch, FILE *fp);  // for printf

#endif /* UART_H_ */