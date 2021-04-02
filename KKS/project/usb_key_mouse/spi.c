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
	sbi(DDRB,0); //SS
	sbi(DDRB,1); //SCK
	sbi(DDRB,2); //MOSI
	cbi(DDRB,3); //MISO 
	PORTB |= 0x09; //MISO Using Pull up, SS High 
	sbi(SPCR,SPE);
	sbi(SPCR,MSTR);
}

void SPI_Slave_Init(void)
{
	cbi(DDRB,0);
	cbi(DDRB,1);
	cbi(DDRB,2);
	sbi(DDRB,3);
	PORTB = 0xFF;
	sbi(SPCR,SPE);
}

uint8_t SPI_TxRx(uint8_t Data)
{
	SPDR = Data;
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}