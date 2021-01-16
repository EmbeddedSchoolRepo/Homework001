/*
 * TWI.c
 *
 * Created: 2020-11-07 오전 3:21:16
 *  Author: KKS
 */ 
#include "TWI.h"


void i2c_init(void)
{
	/*initallize TWI clock : 400kHz clock, TWPS = 0 -> PRESCALER = 1 */
	TWSR = 0x00;
	TWBR = 12;
}

unsigned char i2c_start(unsigned char address)
{
	uint8_t   twst;

	// send START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits.
	twst = TWSR & 0xF8;
	if ( (twst != TWI_START) && (twst != TWI_RESTART)) return 1;

	// send device address
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wail until transmission completed and ACK/NACK has been received
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits.
	twst = TWSR & 0xF8;
	if ( (twst != TWI_MT_SLA_ACK) && (twst != TWI_MR_SLA_NACK) ) return 1;

	return 0;
}

unsigned char i2c_rep_start(unsigned char address)
{
	return i2c_start(address);
}

void i2c_stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	
	while(TWCR & (1<<TWSTO));
}

unsigned char i2c_write( unsigned char data)
{
	uint8_t twst;
	
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
	
	twst = TWSR & 0xF8;
	if(twst != TWI_MT_DATA_ACK) return 1;
	return 0;
}




unsigned char i2c_readAck(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	
	while(!(TWCR & (1<<TWINT)));
	
	return TWDR;
}

unsigned char i2c_readNak(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));

	return TWDR;
}
