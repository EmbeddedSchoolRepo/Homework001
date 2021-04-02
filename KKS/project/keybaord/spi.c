/*
 * spi.c
 *
 * Created: 2020-12-28 오후 1:01:08
 *  Author: KKS
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define sbi(PORTX,BitX) (PORTX |= (1<<BitX))
#define cbi(PORTX,BitX) (PORTX &= ~(1<<BitX))

void SPI_Master_Init(void)
{
	sbi(DDRB,5);
	sbi(DDRB,3);
	sbi(DDRB,2);
	cbi(DDRB,4);
	PORTB = 0xff;
	sbi(SPCR,SPE);
	sbi(SPCR,MSTR);
}

void SPI_Slave_Init(void)
{
	cbi(DDRB,5);
	cbi(DDRB,3);
	cbi(DDRB,2);
	sbi(DDRB,4);
	PORTB = 0xff;
	sbi(SPCR,SPE);
}

unsigned char SPI_TxRx(unsigned char Data)
{
	SPDR = Data;
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}