/*
 * twi.c
 *
 * Created: 2020-12-16 오후 7:04:32
 *  Author: arohaneul
 */ 
#include "twi.h"

#define TW_STS      0xF8

#define TWI_SCL     0x20
#define TWI_SDA     0x10
#define TWI_RD      0x01
#define TWI_WR      0x00

#define TWI_START         0x08
#define TWI_RESTART         0x10

/* Master Transmitter */
#define TWI_MT_SLA_ACK      0x18
#define TWI_MT_SLA_NACK      0x20
#define TWI_MT_DATA_ACK      0x28
#define TWI_MT_DATA_NACK   0x30
#define TWI_MT_ARB_LOST      0x38

/* Master Receiver */
#define TWI_MR_ARB_LOST      0x38
#define TWI_MR_SLA_ACK      0x40
#define TWI_MR_SLA_NACK      0x48
#define TWI_MR_DATA_ACK      0x50
#define TWI_MR_DATA_NACK   0x58

void i2c_init(void)
{
	/*initialize TWI clockP 100khz clock, TWPS = 0 => prescaler = 1*/
	TWSR = 0x00;
	TWBR = 12;/*((F_CPU / SCL_CLOCK) - 16)/2 = TWBR, F_CPU = 4Mhz, SCL_CLOCK = 100K -- >12 */
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
	
	TWCR = (1<<TWINT) | (1<<TWEN) | ( 1<< TWSTO);
	
	while(TWCR & (1<<TWSTO));
	
}
unsigned char i2c_write(unsigned char data)
{
	
	uint8_t twst;
	
	TWDR = data;
	TWCR = (1 << TWINT) | (1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
	
	twst = TWSR & 0xF8;
	if((twst != TWI_MT_DATA_ACK)) return 1;
	
	return 0;
	
}

/*************************************************************************
Read one byte from the I2C device, request more data from device

Return : byte read from I2C device
*************************************************************************/
unsigned char i2c_readAck(void)//데이터 제대로 받을때 ACK
{
	
	TWCR = (1<<TWINT) | (1<<TWEN) | ( 1<< TWEA);
	while(!(TWCR & ( 1<<TWINT)));
	
	return TWDR;
}

/*************************************************************************
Read one byte from the I2C device, read is followed by a stop condition

Return : byte read from I2C device
*************************************************************************/
unsigned char i2c_readNak(void) //데이터를 제대로 받지 못하였을때
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & ( 1<<TWINT)));
	
	return TWDR;
}