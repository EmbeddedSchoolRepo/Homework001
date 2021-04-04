/*
 * essential.h
 *
 * Created: 2020-12-23 오전 2:47:58
 *  Author: 82107
 */ 


#ifndef ESSENTIAL_H_
#define ESSENTIAL_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <math.h>

#define s_to_us 1000000
#define us_to_s 0.000001F

#define sbi(PORTx, Bit)	PORTx |= (1 << Bit)
#define cbi(PORTx, Bit)	PORTx &= (~(1 << Bit))





#endif /* ESSENTIAL_H_ */