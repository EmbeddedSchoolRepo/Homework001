/*
 * BLDCmotor.c
 *
 * Created: 2020-12-27 오전 2:44:24
 *  Author: 82107
 */ 

#include "essential.h"

SIGNAL (TIMER0_OVF_vect)
{
	OCR0A += 1;
	
	if(OCR0A == 255)
	{
		OCR0A = 0;
	}
	_delay_ms(40);
}

extern void timer_counter_init(void)
{
	TCCR0A = 0xA3;
	TCCR0B = 0xC3; //분주비 64 -> 타이머 주기 1.02ms
	TIMSK0 = 0x03;
	sbi(DDRD, PORTD6); //OC0A
	sbi(DDRD, PORTD5); //OC0B
	
	OCR0A = 0;
	
	sbi(SREG,7);
}

