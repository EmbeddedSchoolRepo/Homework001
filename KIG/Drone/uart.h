/*
 * UART.h
 *
 * Created: 2020-12-23 오전 2:27:44
 *  Author: 82107
 */ 


#ifndef UART_H_
#define UART_H_


void uart_init(void);
void uart_transmit(uint8_t data);
uint8_t uart_receive(void);
void uart_string_transmit(uint8_t* string);
void uart_print(char *name, long val);
int usartTxChar(char ch, FILE *fp);




#endif /* UART_H_ */