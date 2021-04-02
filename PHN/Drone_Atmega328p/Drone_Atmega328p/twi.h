/*
 * twi.h
 *
 * Created: 2020-12-16 오후 7:05:28
 *  Author: arohaneul
 */ 


#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void i2c_init(void);
unsigned char i2c_start(unsigned char address);
unsigned char i2c_rep_start(unsigned char address);
void i2c_stop(void);
unsigned char i2c_write(unsigned char data);
unsigned char i2c_readAck(void);
unsigned char i2c_readNak(void);





#endif /* TWI_H_ */