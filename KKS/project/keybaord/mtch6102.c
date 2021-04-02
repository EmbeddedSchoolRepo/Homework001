/*
 * mtch6102.c
 *
 * Created: 2021-01-12 오전 9:06:59
 *  Author: KKS
 */ 

#define F_CPU 16000000UL

#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "TWI.H"
#include "mtch6102.h"

void mtch6102_int_init(void)
{
	;
}

uint8_t mtch6102_read_8bit(uint8_t reg_address)
{
	uint8_t reg_status;
	
	i2c_start(((uint8_t)TOUCHPAD_DEVICE_SLAVE_ADDR<<1)|I2C_WRITE);
	i2c_write(reg_address);//TOUCHPAD_REG_TOUCH_STATE
	i2c_rep_start(((uint8_t)TOUCHPAD_DEVICE_SLAVE_ADDR<<1)|I2C_READ);
	
	reg_status = i2c_readNak();
	i2c_stop();
	
	return reg_status;
}

void mtch6102_write_8bit(uint8_t reg_address ,uint8_t* i2c_data_buffer)
{
	i2c_start(((uint8_t)TOUCHPAD_DEVICE_SLAVE_ADDR<<1)|I2C_WRITE);
	i2c_write(reg_address);
	i2c_write(*i2c_data_buffer);
	i2c_stop();
}

void mtch6102_dump_reigster(void)
{
	mtch6102_read_xy_pos();
	mtch6102_read_touch_status();
}

void mtch6102_read_touch_status(void)
{
	uint8_t touch_status;
	
	touch_status = mtch6102_read_8bit(TOUCHPAD_REG_TOUCH_STATE);
	
	switch(touch_status&(0x07)) //low 3bit 추출
	{
		case 1:
			printf("touch_here!\n");
			break;
		case 2:
			printf("Gestur_here\n");
			break;
		case 4:
			printf("Large_Activatiaon_here\n");
			break;
		default :
			break;
	}
	
	
}

void mtch6102_read_xy_pos(void)
{
	mtch6102_pos cur_pos;	
	
	cur_pos.lsb = mtch6102_read_8bit(TOUCHPAD_REG_TOUCH_LSB);
	_delay_us(10); //necessary 
	cur_pos.x_11_4 = mtch6102_read_8bit(TOUCHPAD_REG_TOUCH_X);
	_delay_us(10);
	cur_pos.y_11_4 = mtch6102_read_8bit(TOUCHPAD_REG_TOUCH_Y);
	_delay_us(10);
	cur_pos.xpos = ((cur_pos.x_11_4)<<4)|((cur_pos.lsb>>4)&0x0f);
	cur_pos.ypos = ((cur_pos.y_11_4)<<4)|(cur_pos.lsb&0x0f);
	
	printf("cur_pos.xpos : %d, cur_pos.ypos : %04d\r",cur_pos.xpos,cur_pos.ypos);
}


ISR(INT0_vect)
{
	phase = 3;
}
