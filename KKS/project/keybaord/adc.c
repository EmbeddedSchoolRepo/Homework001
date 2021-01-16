/*
 * adc.c
 *
 * Created: 2021-01-11 오후 2:43:20
 *  Author: KKS
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "adc.h"

#define sbi(PORTX,BitX) (PORTX |= (1<<BitX))
#define cbi(PORTX,BitX) (PORTX &= ~(1<<BitX))

void adc_init(void)
{
	ADMUX |= ADC8|AREF_1_1V;
	sbi(ADCSRA,ADEN);
}

uint16_t adc_read(void)
{
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA&(1<<ADIF)));
	return ((((uint16_t)ADCH)<<8)|(ADCL));
}

void adc_stop(void)
{
	cbi(ADCSRA,ADEN);
}

void gen_random_add(uint8_t* add)
{
	uint8_t i;
	
	srand(adc_read());
	
	for(i=0;i<5;i++)
	{
		*add = rand()%(0xff);
		add++;
	}
}