/*
 * TWI_COM.c
 *
 * Created: 2020-11-07 오전 2:18:29
 * Author : SON
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
	TWSR = 0x00;
	TWBR = 12;
}

unsigned char i2c_start(unsigned char address)
{
	uint8_t twst;
	
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
	
	twst = TWSR & 0xF8;
	
	if((twst != TWI_START) && (twst != TWI_RESTART)) return 1;
	
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
	
	twst = TWSR & 0xF8;
	if((twst != TWI_MT_SLA_ACK) && (twst != TWI_MR_SLA_NACK)) return 1;
	
	return 0;
}//i2c_start

unsigned char i2c_rep_start(unsigned char address)
{
	return  i2c_start(address);
}//i2c_rep_start

void i2c_stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	
	while(TWCR & (1<<TWSTO));
}//i2c_stopm-

unsigned char i2c_write(unsigned char data)
{
	uint8_t twst;
	
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));
	
	twst = TWSR & 0xF8;
	if(twst != TWI_MT_DATA_ACK) return 1;
	
	return 0;
}//i2c_write

unsigned char i2c_readAck(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	
	return TWDR;
}//i2c_readAck

unsigned char i2c_readNak(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
	return TWDR;
}//i2c_readNak

