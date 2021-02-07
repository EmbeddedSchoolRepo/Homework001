/*
 * MPU6050.c
 *
 * Created: 2020-12-01 오후 3:50:10
 *  Author: SPH
 */ 
#include "MPU6050.h"

#define PI 3.14159265358F

#define Accel_Roll_Offset 0
#define Accel_Pitch_Offset 0
#define Accel_Yaw_Offset 0

#define Gyro_Roll_Offset 0
#define Gyro_Pitch_Offset 0
#define Gyrol_Yaw_Offset 0

static Angle_3Dim Accel_Angle;
static Angle_3Dim Gyro_Angle;

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
	//Register : PWR management1, Set Bit : SLEEP MODE, Set SLEEP MODE Bit length : 1, Disable SLEEP MODE
	MPU6050_WriteBits(PWR_MGMT_1, SLEEP_MODE_BIT, SLEEP_MODE_LEN, DISABLE);
	
	//Register : PWR management1, Set Bit : CLK Select, Set CLK Select length : 3, Set CLK source : PLL with X axis gyroscope reference
	MPU6050_WriteBits(PWR_MGMT_1, CLKSEL_BIT, CLKSEL_LEN, CLKSEL1);
	
	//Register : Interrupt Enable, Set Bit : DATA_RDY_INT_EN, Set DATA_RDY_INT_EN length : 1, Enable DATA_RDY_INT
	//MPU6050_WriteBits(INT_ENABLE, DATA_RDY_INT_EN, DATA_RDY_INT_EN_LEN, ENABLE);
	
	//Register : Configuration, Set Bit : Digital LowPassFilter Config, Set DLPF Bit length : 3, 
	//Set DLPF config3 : Accele = 44Hz(Bandwidth), 4.9ms(Delay), Fs = 1KHz / Gyro = 42Hz(Bandwidth), 4.8ms(Delay), Fs = 1KHz -> 2020.12.07
	//Set DLPF config0 : Accele = 260Hz(Bandwidth), 0ms(Delay), Fs = 1KHz / Gyro = 256Hz(Bandwidth), 0.98ms(Delay), Fs = 8KHz -> 2020.12.28
	MPU6050_WriteBits(CONFIG, DLPF_CFG_BIT, DLPF_CFG_LEN, DLPF_CFG0);
	
	//Register : Sample Rate, Writes 0x04 : Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV(=4))
	//where Gyroscope Output Rate = 8kHz when the DLPF is disabled (DLPF_CFG = 0 or 7), and 1kHz
	//when the DLPF is enabled
	MPU6050_WriteByte(SMPLRT_DIV, 4);
	
	//Register : Gyro Configuration, Set Bit : Gyro Full Scale, Set Bit length : 2, Set Gyro Full Scale : +,-2000 degree/s
	MPU6050_WriteBits(GYRO_CONFIG, GYRO_FS_SEL_BIT, GYRO_FS_SEL_LEN, GYRO_FS_SEL2000);
	
	//Register : Accelerometer Configuration, Set Bit : Accelerometer Full Scale, Set Bit length : 2, Set Accel Full Scale : +,-16g
	MPU6050_WriteBits(ACCEL_CONFIG, ACCEL_AFS_SEL_BIT, ACCEL_AFS_SEL_LEN, ACCEL_AFS_SEL16G);
	
	_delay_ms(30);
	
	Gyro_Angle.Roll = 0;
	Gyro_Angle.Pitch = 0;
	Gyro_Angle.Yaw = 0;
	
	Accel_Angle.Roll = 0;
	Accel_Angle.Pitch = 0;
	Accel_Angle.Yaw = 0;
}

//Get MPU6050 Accelerometer & Gyro RawData
void get_MPU6050_RawData(pAxis_Data Accel_Data, pAxis_Data Gyro_Data)
{	
	uint8_t buffer[14] = {0,};
	MPU6050_ReadBytes(ACCEL_XOUT_H, 14, buffer);
	
	Accel_Data->Xaxis = (uint16_t)buffer[0] << 8 | buffer[1];
	Accel_Data->Yaxis = (uint16_t)buffer[2] << 8 | buffer[3];
	Accel_Data->Zaxis = (uint16_t)buffer[4] << 8 | buffer[5];
	
	Gyro_Data->Xaxis = (uint16_t)buffer[8] << 8 | buffer[9];
	Gyro_Data->Yaxis = (uint16_t)buffer[10] << 8 | buffer[11];
	Gyro_Data->Zaxis = (uint16_t)buffer[12] << 8 | buffer[13];
}

void Calc_Accel_RollPitch(pAxis_Data AccelData, pAngle_3Dim Accel_Angle)
{
	Angle_3Dim Angle_Tmp;
	
	Angle_Tmp.Roll = (double)AccelData -> Xaxis / (double)ACCEL_LSB_FS16G;
	Angle_Tmp.Pitch = (double)AccelData -> Yaxis / (double)ACCEL_LSB_FS16G;
	Angle_Tmp.Yaw = (double)AccelData -> Zaxis / (double)ACCEL_LSB_FS16G;
	
	Accel_Angle->Roll = atan2(Angle_Tmp.Pitch, Angle_Tmp.Yaw) * 180.0F / (double)PI;
	Accel_Angle->Pitch = atan2(Angle_Tmp.Roll, Angle_Tmp.Yaw) * 180.0F / (double)PI;
	
	#ifdef ForTestMPU6050
	printf("Roll = %.2f\tPitch = %.2f\n", Accel_Angle->Roll, Accel_Angle->Pitch);
	#endif
}

void Calc_GyroData(pAxis_Data GyroData, pAngle_3Dim Gyro_Angle)
{
	Gyro_Angle->Roll = (double)GyroData->Xaxis / (double)GYRO_LSB_FS2000;
	Gyro_Angle->Pitch = (double)GyroData->Yaxis / (double)GYRO_LSB_FS2000;
	Gyro_Angle->Yaw = (double)GyroData->Zaxis / (double)GYRO_LSB_FS2000;	
}

void Integral_GyroData(pAxis_Data GyroData, pAngle_3Dim Gyro_Angle)
{
	Angle_3Dim Angle_Tmp;
	
	Angle_Tmp.Roll = 0;
	Angle_Tmp.Pitch = 0;
	Angle_Tmp.Yaw = 0;
		
	Angle_Tmp.Roll = (double)GyroData->Xaxis / (double)GYRO_LSB_FS2000;
	Angle_Tmp.Pitch = (double)GyroData->Yaxis / (double)GYRO_LSB_FS2000;
	Angle_Tmp.Yaw = (double)GyroData->Zaxis / (double)GYRO_LSB_FS2000;
	
	Gyro_Angle->Roll = Angle_Tmp.Roll*(double)dt + Gyro_Angle->Roll;
	Gyro_Angle->Pitch = Angle_Tmp.Pitch*(double)dt + Gyro_Angle->Pitch;
	Gyro_Angle->Yaw = Angle_Tmp.Yaw*(double)dt + Gyro_Angle->Yaw;
	
	#ifdef ForTestMPU6050
	printf("Gyro Roll = %.2f\tGyro Pitch = %.2f\tGyro Yaw = %.2f\n", Gyro_Angle->Roll,Gyro_Angle->Pitch,Gyro_Angle->Yaw);
	#endif
}

void RunMPU6050(void)
{
	Axis_Data_Struct Accel_Data;	
	Axis_Data_Struct Gyro_Data;
	
	get_MPU6050_RawData(&Accel_Data, &Gyro_Data);
	
	Calc_Accel_RollPitch(&Accel_Data, &Accel_Angle);
	Integral_GyroData(&Gyro_Data, &Gyro_Angle);
	
	#ifdef Filter_EN
	Calc_GyroData(&Gyro_Data, &Gyro_Angle);
	#else
	Integral_GyroData(&Gyro_Data, &Gyro_Angle);
	#endif
}

pAngle_3Dim getAcceleroData(void)
{
	pAngle_3Dim pTmp = &Accel_Angle;
	return pTmp;
}

pAngle_3Dim getGyroData(void)
{
	pAngle_3Dim pTmp = &Gyro_Angle;
	return pTmp;
}