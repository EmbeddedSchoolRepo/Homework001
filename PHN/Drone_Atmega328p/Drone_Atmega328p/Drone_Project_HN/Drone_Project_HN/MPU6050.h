/*
 * MPU6050.h
 *
 * Created: 2021-01-31 오후 12:18:48
 *  Author: phn15
 */ 


#ifndef MPU6050_H_
#define MPU6050_H_

#define I2C_WRITE   0
#define I2C_READ   1

#define ENABLE 1
#define DISABLE 0

#define MPU6050_ADDR0 0x68

#define SMPLRT_DIV 0x19

//Configuration Register & Setting Value
#define CONFIG 0x1A
#define DLPF_CFG0 0 //Accel Delay : 0, Gyro Delay : 0.98
#define DLPF_CFG1 1 //Accel Delay : 2.0, Gyro Delay : 1.9
#define DLPF_CFG2 2 //Accel Delay : 3.0, Gyro Delay : 2.8
#define DLPF_CFG3 3 //Accel Delay : 4.9, Gyro Delay : 4.8
#define DLPF_CFG4 4 //Accel Delay : 8.5, Gyro Delay : 8.3
#define DLPF_CFG5 5 //Accel Delay : 13.8, Gyro Delay : 13.4
#define DLPF_CFG6 6 //Accel Delay : 19.0, Gyro Delay : 18.6
#define DLPF_CFG7 7 //Accel Delay : rvd, Gyro Delay : rvd

//GYRO Configuration Register & Setting Value
#define GYRO_CONFIG 0x1B
#define GYRO_FS_SEL250 0 //+-250degree/s
#define GYRO_FS_SEL500 1 //+-500degree/s
#define GYRO_FS_SEL1000 2 //+-1000degree/s
#define GYRO_FS_SEL2000 3 //+-2000degree/s


//ACCEL Configuration Register & Setting Value
#define ACCEL_CONFIG 0x1C
#define ACCEL_AFS_SEL2G 0 //+-2G
#define ACCEL_AFS_SEL4G 1 //+-4G
#define ACCEL_AFS_SEL8G 2 //+-8G
#define ACCEL_AFS_SEL16G 3 //+-16G


/*Accelerometer Data Out Register*/
#define ACCEL_XOUT_H 0x3B


//PWR_MGMT_1 : the power mode and clock source & resetting
#define PWR_MGMT_1 0x6B
#define CLKSEL0 0	//8MHz
#define CLKSEL1 1	//PLL with X axis gyro
#define CLKSEL2 2	//PLL with Y axis gyro
#define CLKSEL3 3	//PLL with Z axis gyro
#define CLKSEL4 4	//PLL with external 32.768kHz
#define CLKSEL5 5	//PLL with external 32.768kHz
#define CLKSEL6 6	//Rvd
#define CLKSEL7 7	//Stops the clock and keeps the timing generator in reset

//Gyro & Accel Scale Factor
#define ACC_2G                      16384    //  AFS_SEL= 0: Full Scale = +/-2G
#define ACC_4G                      8192     //  AFS_SEL= 1: Full Scale = +/-4G
#define ACC_8G                      4096     //  AFS_SEL= 2: Full Scale = +/-8G
#define ACC_16G                     2048     //  AFS_SEL= 3: Full Scale = +/-16G
#define GYRO_250D                   131      //  FS_SEL = 0: Full scale set to 250 deg/sec
#define GYRO_500D                   65.5     //  FS_SEL = 1: Full scale set to 500 deg/sec
#define GYRO_1000D                  32.8     //  FS_SEL = 2: Full scale set to 1000 deg/sec
#define GYRO_2000D                  16.4     //  FS_SEL = 3: Full scale set to 2000 deg/sec

typedef struct
{
	int16_t Xaxis;
	int16_t Yaxis;
	int16_t Zaxis;
	
}Axis_Struct;

typedef struct
{
	double ROLL;
	double PITCH;
	double YAW;
	
}_3DAngle_Struct;

typedef Axis_Struct* pAxis_Data;
typedef _3DAngle_Struct* p3D_Data;

void mpu6050_writeByte(uint8_t regAddr, uint8_t data);
uint8_t mpu6050_readBytes(uint8_t regAddr, uint8_t length, uint8_t *data);

void init_MPU6050(void);
void getData_MPU6050(pAxis_Data Accel_RawData, pAxis_Data Gyro_RawData);
void Calib_Parameter(pAxis_Data Accel_RawData, pAxis_Data Gyro_RawData, p3D_Data Accel_Angle, p3D_Data Gyro_Angle, p3D_Data Angle_Comp);
void compute_MPU6050(void);
#endif /* MPU6050_H_ */