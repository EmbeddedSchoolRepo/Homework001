/*
 * i2c.c
 *
 * Created: 2020-12-23 오전 3:47:35
 *  Author: 82107
 */ 
#include "essential.h"
#include "uart.h"

#define START 0x08
#define REP_START 0x10
#define MT_SLA_W_ACK 0x18
#define MT_DATA_ACK 0x28

#define TWI_MT_SLA_NACK	0x20


#define MR_SLA_R_ACK 0x40
#define MR_SLA_R_NACK 0x48
#define MR_DATA_ACK 0x50
#define MR_DATA_NACK 0x58

#define WRITE 0
#define READ 1

void i2c_init(void)
{
	TWSR= 0x00; //프리스케일러 1
	TWBR = 12; //통신속도 400KHz
}

uint8_t i2c_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);
	while(!(TWCR & (1<<TWINT)));
	
	if(((TWSR & 0xF8) != START) && (TWSR & 0xF8) != REP_START)
	{
		printf("start condition error\n");
		i2c_start();
	}
	return 0;
}

void i2c_rep_start(void)
{
	i2c_start();
}

void i2c_stop(void)
{
	TWCR = (1<<TWINT | (1<<TWEN)) | (1<<TWSTO);
	
	while(TWCR & (1<<TWSTO));

}

uint8_t i2c_SLA_W(uint8_t address)
{
	//SLA+W
	TWDR = (address<<1) | WRITE;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));

	if((TWSR & 0xF8) != MT_SLA_W_ACK)
	{
		printf("MT_SLA_W_ACK error\n");
		i2c_SLA_W(address);
	}
	return 0;
}
uint8_t i2c_write_data(uint8_t data)
{	
	//DATA
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
	if((TWSR & 0xF8) != MT_DATA_ACK)
	{
		printf("MT_DATA_ACK error\n");
		i2c_write_data(data);
	}
	return 0;
}

uint8_t i2c_SLA_R(uint8_t address)
{
	//SLA_R
	TWDR = (address << 1) | READ;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
	if((TWSR & 0xF8) != MR_SLA_R_ACK)
	{
		printf("MR_SLA_R_ACK error\n");
		i2c_SLA_R(address);
	}

	return 0;
}

uint8_t i2c_readACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
		
	if((TWSR & 0xF8) != MR_DATA_ACK)
	{
		printf("MR_DATA_ACK error\n");
		i2c_readACK();
	}	
	return TWDR;
}

uint8_t i2c_readNACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));

	if((TWSR & 0xF8) != MR_DATA_NACK)
	{
		printf("MR_DATA_NACK error\n");
		i2c_readNACK();
	}
	return TWDR;
}