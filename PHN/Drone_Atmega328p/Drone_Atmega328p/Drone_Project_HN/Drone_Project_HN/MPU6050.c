/*
 * MPU6050.c
 *
 * Created: 2021-01-31 오후 12:18:34
 *  Author: phn15
 */ 
#include <avr/io.h>										/* Include AVR std. library file */
#include <util/delay.h>									/* Include delay header file */
#include <stdlib.h>										/* Include standard library file */
#include <stdio.h>
#include <math.h>

#include "MPU6050.h"
#include "twi.h"

#define PI 3.14159265358F
const double RADIANS_TO_DEGREE = 180.0F / (double)PI;

#define dt 0.001F //TimerInterrupt Period = 1ms

int16_t Accel_Zero[3] = {0,};  // 영점 보정값
int16_t Gyro_Zero[3] = {0,};  // 영점 보정값
	
_3DAngle_Struct Accel_AngleData;
_3DAngle_Struct Gyro_AngleData;

void mpu6050_writeByte(uint8_t regAddr, uint8_t data)
{
	i2c_start((MPU6050_ADDR0 << 1) | I2C_WRITE );
	i2c_write(regAddr); //reg
	i2c_write(data);
	i2c_stop();
	
}

uint8_t mpu6050_readBytes(uint8_t regAddr, uint8_t length, uint8_t *data)
{
	uint8_t i=0, count=0;
	
	if( length > 0 )
	{
		i2c_start((MPU6050_ADDR0 << 1) | I2C_WRITE);
		i2c_write(regAddr);

		i2c_rep_start((MPU6050_ADDR0 << 1) | I2C_READ);
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

void init_MPU6050(void)
{
	_delay_ms(150);		// Power up time >100ms

	mpu6050_writeByte(PWR_MGMT_1, DISABLE);//DEVICE RESET 1
	mpu6050_writeByte(PWR_MGMT_1, CLKSEL1);//PLL with X axis gyro
	mpu6050_writeByte(CONFIG, DLPF_CFG0); //Accel Delay : 0, Gyro Delay : 0.98
	mpu6050_writeByte(SMPLRT_DIV, 4);//8khz/ (1+4)=1600Hz
	mpu6050_writeByte(GYRO_CONFIG, GYRO_FS_SEL2000); //GYRO Full Scale +-2000degree/s
	mpu6050_writeByte(ACCEL_CONFIG, ACCEL_AFS_SEL16G); //ACCEL Full Scale 16G

	Accel_AngleData.ROLL = 0;
	Accel_AngleData.PITCH = 0;
	Accel_AngleData.YAW = 0;
	
	Gyro_AngleData.ROLL = 0;
	Gyro_AngleData.PITCH = 0;
	Gyro_AngleData.YAW = 0;

}

void getData_MPU6050(pAxis_Data Accel_RawData, pAxis_Data Gyro_RawData)
{
	
	uint8_t buffer[14] = {0,};
	mpu6050_readBytes(ACCEL_XOUT_H, 14, buffer);
	
	Accel_RawData->Xaxis = buffer[0] >> 8 | buffer[1]; //0x3b~3c
	Accel_RawData->Yaxis = buffer[2] >> 8 | buffer[3]; //0x3d~3e
	Accel_RawData->Zaxis = buffer[4] >> 8 | buffer[5]; //0x3f~40
	
	Gyro_RawData->Xaxis = buffer[8] >> 8 | buffer[9];
	Gyro_RawData->Yaxis = buffer[10] >> 8 | buffer[11]; 
	Gyro_RawData->Zaxis = buffer[12] >> 8 | buffer[13]; 
}

void offset_remove(pAxis_Data Accel_RawData, pAxis_Data Gyro_RawData, pAxis_Data Accel_Zero, pAxis_Data Gyro_Zero)
{

	Axis_Struct Acc_Sum;
	Axis_Struct Gyro_Sum;
	
	uint16_t repeat = 1000;

	getData_MPU6050(Accel_RawData, Gyro_RawData);
	_delay_ms(2);
	
	//Sum Value
	Acc_Sum.Xaxis += Accel_RawData->Xaxis;
	Acc_Sum.Yaxis += Accel_RawData->Yaxis;
	Acc_Sum.Zaxis += Accel_RawData->Zaxis;
	
	Gyro_Sum.Xaxis += Gyro_RawData->Xaxis;
	Gyro_Sum.Yaxis += Gyro_RawData->Yaxis;
	Gyro_Sum.Zaxis += Gyro_RawData->Zaxis;
	
	//Average Value
	Accel_Zero->Xaxis = Acc_Sum.Xaxis / repeat;
	Accel_Zero->Yaxis = Acc_Sum.Xaxis / repeat;
	Accel_Zero->Zaxis = Acc_Sum.Xaxis / repeat;
	
	Gyro_Zero->Xaxis = Gyro_Sum.Xaxis / repeat;
	Gyro_Zero->Yaxis = Gyro_Sum.Xaxis / repeat;
	Gyro_Zero->Zaxis = Gyro_Sum.Xaxis / repeat;

}
void Calib_Parameter(pAxis_Data Accel_RawData, pAxis_Data Gyro_RawData, p3D_Data Accel_Angle, p3D_Data Gyro_Angle, p3D_Data Angle_Comp)
{

	double AccAgl_x, AccAgl_y, AccAgl_z;
	double GyrAgl_x, GyrAgl_y, GyrAgl_z;
	
	//  Calculate Accel angle = 2048 : Full scale +/-16G
	AccAgl_x = (double)Accel_RawData->Xaxis / (double)ACC_16G;
	AccAgl_y = (double)Accel_RawData->Yaxis / (double)ACC_16G;
	AccAgl_z = (double)Accel_RawData->Zaxis / (double)ACC_16G;
	
	//  Calculate PITCH ROLL angle 
	Accel_Angle->ROLL = atan2((-1) * AccAgl_x, sqrt(AccAgl_y*AccAgl_y + AccAgl_z*AccAgl_z)) * 180.0F / (double)PI;
	Accel_Angle->PITCH = atan2(AccAgl_y, sqrt(AccAgl_x*AccAgl_x + AccAgl_z*AccAgl_z)) * 180.0F / (double)PI;
	Accel_Angle->YAW = 0;
	
	printf("Accel_Angle Roll, Pitch, Yaw= %f %f %f\n", (double)Accel_Angle->ROLL , (double)Accel_Angle->PITCH, (double)Accel_Angle->YAW );
	
	//	Calculate gyro angle = 16.4 : Full scale +/-16G
	GyrAgl_x = (double)Gyro_RawData->Xaxis / (double)GYRO_2000D;
	GyrAgl_y = (double)Gyro_RawData->Yaxis / (double)GYRO_2000D;
	GyrAgl_z = (double)Gyro_RawData->Zaxis / (double)GYRO_2000D;
	
	Gyro_Angle->ROLL = GyrAgl_x*(double)dt + Gyro_Angle->ROLL;
	Gyro_Angle->PITCH = GyrAgl_y*(double)dt + Gyro_Angle->PITCH;
	Gyro_Angle->YAW = GyrAgl_z*(double)dt + Gyro_Angle->YAW;
		
	printf("Gyro_Angle Roll, Pitch, Yaw= %f %f %f\n", (double)Gyro_Angle->ROLL , (double)Gyro_Angle->PITCH, (double)Gyro_Angle->YAW );

	//  Calculate 상보필터 (각도를 구하기 위해 dt를 곱하고, 4를 다시 곱해 원래의 raw값으로 복원)
	Angle_Comp->ROLL   = 0.93 * (Angle_Comp->ROLL  + Gyro_Angle->ROLL * 4 * dt )  + 0.07 * Accel_Angle->ROLL;
	Angle_Comp->PITCH   = 0.93 * (Angle_Comp->PITCH  + Gyro_Angle->PITCH * 4 * dt )  + 0.07 * Accel_Angle->PITCH;
	Angle_Comp->YAW  -= Gyro_Angle->YAW * 4 * dt ;
	
	printf("Angle_Comp Roll, Pitch, Yaw= %f %f %f\n\n", (double)Angle_Comp->ROLL, (double)Angle_Comp->PITCH, (double)Angle_Comp->YAW);
	
}

void compute_MPU6050(void)
{

	_3DAngle_Struct Accel_Angle;
	_3DAngle_Struct Gyro_Angle;
	_3DAngle_Struct Angle_Comp;
	Axis_Struct Accel_RawData;
	Axis_Struct Gyro_RawData;
	Axis_Struct Accel_Zero;
	Axis_Struct Gyro_Zero;

	offset_remove(&Accel_RawData, &Gyro_RawData, &Accel_Zero, &Gyro_Zero);
	
	// 영점 조정하기
	Accel_RawData.Xaxis  -= Accel_Zero.Xaxis ;
	Accel_RawData.Yaxis  -= Accel_Zero.Yaxis ;
	Accel_RawData.Zaxis  -= Accel_Zero.Zaxis ;
	Gyro_RawData.Xaxis  -= Gyro_Zero.Xaxis;
	Gyro_RawData.Yaxis  -= Gyro_Zero.Yaxis;
	Gyro_RawData.Zaxis  -= Gyro_Zero.Zaxis;
	
	Calib_Parameter(&Accel_RawData, &Gyro_RawData, &Accel_Angle, &Gyro_Angle, &Angle_Comp);
	
} 