/*
 * MPU6050.c
 *
 * Created: 2020-12-01 오후 3:50:10
 *  Author: SPH
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "MPU6050.h"
#include "twi.h"
#include "uart.h"

#define PI 3.14159265358

static Angle_3Dim Angle;
static uint8_t buffer[14];

uint8_t MPU6050_ReadBytes(uint8_t reg_addr, uint8_t len, uint8_t* pData)
{
	uint8_t cnt = 0;
	if(len > 0)
	{
		i2c_start((MPU6050_ADD0 << 1) | I2C_WRITE);
		i2c_write(reg_addr);
		i2c_rep_start((MPU6050_ADD0 << 1) | I2C_READ);
		
		for(int i = 0; i < len; i++)
		{
			cnt++;
			if(i == len-1) 
				pData[i] = i2c_readNak();
			else 
				pData[i] = i2c_readAck();
		}
	}	
	i2c_stop();
	return cnt;
}

uint8_t MPU6050_ReadByte(uint8_t reg_addr, uint8_t* pData)
{
	return MPU6050_ReadBytes(reg_addr, 1, pData);
}

void MPU6050_WriteBytes(uint8_t reg_addr, uint8_t len, uint8_t* pData)
{
	if(len > 0)
	{
		i2c_start((MPU6050_ADD0 << 1) | I2C_WRITE);
		i2c_write(reg_addr);
		for(int i = 0; i < len; i++)
		i2c_write((uint8_t)pData[i]);
	}
	
	i2c_stop();
}

void MPU6050_WriteByte(uint8_t reg_addr, uint8_t data)
{
	MPU6050_WriteBytes(reg_addr, 1, &data);
}

void MPU6050_WriteBits(uint8_t reg_addr, uint8_t bit, uint8_t len, uint8_t data)
{
	if(len > 0)
	{
		uint8_t tmp = 0;
		if(MPU6050_ReadByte(reg_addr, &tmp) != 0)
		{
			uint8_t mask = ((1 << len) - 1) << (bit - len + 1);
			data <<= (bit - len + 1);
			data &= mask;
			tmp &= ~mask;
			tmp |= data;
		}
		MPU6050_WriteByte(reg_addr, tmp);
	}
}

void InitMPU6050(void)
{
	MPU6050_WriteBits(PWR_MGMT_1, SLEEP_MODE_BIT, SLEEP_MODE_LEN, DISABLE);
	//_delay_ms(10);
	MPU6050_WriteBits(PWR_MGMT_1, CLKSEL_BIT, CLKSEL_LEN, CLKSEL1);
	MPU6050_WriteBits(CONFIG, DLPF_CFG_BIT, DLPF_CFG_LEN, DLPF_CFG3);
	MPU6050_WriteByte(SMPLRT_DIV, 4);
	MPU6050_WriteBits(GYRO_CONFIG, GYRO_FS_SEL_BIT, GYRO_FS_SEL_LEN, GYRO_FS_SEL2000);
	MPU6050_WriteBits(ACCEL_CONFIG, ACCEL_AFS_SEL_BIT, ACCEL_AFS_SEL_LEN, ACCEL_AFS_SEL16G);
}

Accel_Data_Struct getAccelData(void)
{	
	Accel_Data_Struct Accel_Raw;
	MPU6050_ReadBytes(ACCEL_XOUT_H, 14, buffer);
	
	Accel_Raw.Accel_Xaxis = (uint16_t)buffer[0] << 8 | buffer[1];
	Accel_Raw.Accel_Yaxis = (uint16_t)buffer[2] << 8 | buffer[3];
	Accel_Raw.Accel_Zaxis = (uint16_t)buffer[4] << 8 | buffer[5];
	
	printf("X-axis = %f\n", (float)Accel_Raw.Accel_Xaxis / (float)ACCEL_LSB_FS16G);
	printf("Y-axis = %f\n", (float)Accel_Raw.Accel_Yaxis / (float)ACCEL_LSB_FS16G);
	printf("Z-axis = %f\n", (float)Accel_Raw.Accel_Zaxis / (float)ACCEL_LSB_FS16G);
	
	return Accel_Raw;
}

pAngle_3Dim CalcRollPitch(pAccel_Data AccelData)
{
	pAngle_3Dim pAngle = NULL;
	Angle_3Dim Angle_Tmp;
	pAngle = &Angle;
	
	Angle_Tmp.Roll = (double)AccelData -> Accel_Xaxis / (double)ACCEL_LSB_FS16G;
	Angle_Tmp.Pitch = (double)AccelData -> Accel_Yaxis / (double)ACCEL_LSB_FS16G;
	Angle_Tmp.Yaw = (double)AccelData -> Accel_Zaxis / (double)ACCEL_LSB_FS16G;
	
	pAngle->Roll = atan2(Angle_Tmp.Pitch, Angle_Tmp.Yaw) * 180.0F / (double)PI;
	pAngle->Pitch = atan2(Angle_Tmp.Roll, Angle_Tmp.Yaw) * 180.0F / (double)PI;
	
	return pAngle;
}

pAngle_3Dim RunMPU6050(void)
{
	pAngle_3Dim Angle_Result = NULL;
	Accel_Data_Struct Accel_Data;
	
	Accel_Data = getAccelData();
	
	Angle_Result = CalcRollPitch(&Accel_Data);
	
	return Angle_Result;
}