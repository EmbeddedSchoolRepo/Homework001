/*
 * MPU6050.c
 *
 * Created: 2021-01-09 오전 8:13:28
 *  Author: phn15
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "MPU6050.h"
#include "twi.h"
#include "uart.h"

uint8_t buffer[14];
int16_t Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;



uint8_t mpu6050_readBytes(uint8_t regAddr, uint8_t length, uint8_t *data)
{
	uint8_t i=0, count=0;
	
	if( length > 0 )
	{
		i2c_start((MPU6050_ADDR0 << 1) | I2C_WRITE);
		i2c_write(regAddr);

		i2c_start((MPU6050_ADDR0 << 1) | I2C_READ);
		for( i = 0 ; i < length ; i++ )
		{
			count++;
			if( i == ( length - 1 )) 
				data[i] = i2c_readNak();
			else             
				data[i] = i2c_readAck();
		}
		i2c_stop();
	}
	return count;
}

void mpu6050_writeByte(uint8_t regAddr, uint8_t data)
{
	i2c_start((MPU6050_ADDR0 << 1) | I2C_WRITE );
	i2c_write(regAddr); //reg
	i2c_write(data);
	i2c_stop();
}

uint8_t mpu6050_readBit(uint8_t regAddr, uint8_t bitNum, uint8_t *data)
{
	uint8_t b;
	uint8_t count= mpu6050_readBytes(regAddr, 1, &b);
	*data=b&(1<<bitNum);
	return count;
}

void mpu6050_writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data)
{
	  //      010 value to write
	  // 76543210 bit numbers
	  //    xxx   args: bitStart=4, length=3
	  // 00011100 mask byte
	  // 10101111 original value (sample)
	  // 10100011 original & ~mask
	  // 10101011 masked | value
	uint8_t mask, b;
	if( mpu6050_readBytes( regAddr, 1, &b ) != 0 )
	{    //get current data
		mask = (( 1 << length ) - 1 ) << ( bitStart - length + 1 );
		data <<= ( bitStart - length + 1 ); // shift data into correct position
		data &= mask;                 // zero all non-important bits in data
		b &= ~(mask);                 // zero all important bits in existing byte
		b |= data;                    // combine data with existing byte
		mpu6050_writeByte(regAddr, b);
	}
}

void mpu6050_init()
{
	_delay_ms(150);
	//set clock source
	//  it is highly recommended that the device be configured to use one of the gyroscopes (or an external clock source)
	//  as the clock reference for improved stability
	mpu6050_setSleepDisable();
	mpu6050_writeBits(PWR_MGMT_1, CLKSEL_BIT, CLKSEL_LENGTH, CLKSEL1);//PLL with X axis gyro
	//set DLPF bandwidth to 42Hz
	mpu6050_writeBits(CONFIG,DLPF_CFG_BIT,DLPF_CFG_LENGTH, DLPF_CFG3); //Accel Delay : 4.9, Gyro Delay : 4.8
	//set sampe rate
	mpu6050_writeByte(SMPLRT_DIV, 4);//1khz/ (1+4)=200Hz
	//set gyro range
	mpu6050_writeBits(GYRO_CONFIG, GYRO_FS_SEL_BIT, GYRO_FS_SEL_LENGTH, GYRO_FS_SEL2000); //GYRO Full Scale 2000/s
	//set accel range
	mpu6050_writeBits(ACCEL_CONFIG, ACCEL_AFS_SEL_BIT, ACCEL_AFS_SEL_LENGTH,ACCEL_AFS_SEL16G); //ACCEL Full Scale 16G
}
//sleep mode
void mpu6050_setSleepDisable(void)
{
	mpu6050_writeBits(PWR_MGMT_1, SLEEP, 1, 0);
}
void mpu6050_getRawValue(void)
{

	
	mpu6050_readBytes(ACCEL_XOUT_H, 14, buffer);
	
	Acc_x = (uint16_t)buffer[0] << 8 | buffer[1];
	Acc_y = (uint16_t)buffer[2] << 8 | buffer[3];
	Acc_z = (uint16_t)buffer[4] << 8 | buffer[5];
	//Gyro_x = (uint16_t)buffer[6] << 8 | (uint16_t)buffer[7]; 
	//Gyro_y = (uint16_t)buffer[8] << 8 | (uint16_t)buffer[9]; 
	//Gyro_z = (uint16_t)buffer[10] << 8 | (uint16_t)buffer[11]; 
	
	printf("X-axis = %lf\n", (float)Acc_x);
	printf("Y-axis = %lf\n", (float)Acc_y);
	printf("Z-axis = %lf\n", (float)Acc_z);

	//mpu6050_viewValue(Acc_x,Acc_y,Acc_z,Gyro_x,Gyro_y,Gyro_z);
	
}
void mpu6050_viewValue(float ax,float ay,float az, float gx,float gy,float gz)
{
	printf("X-axis = %f\n", (float)ax);
	printf("Y-axis = %f\n", (float)ay);
	printf("Z-axis = %f\n", (float)az);

}