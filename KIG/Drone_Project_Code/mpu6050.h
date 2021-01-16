/*
 * MPU6050.h
 *
 * Created: 2020-12-23 오전 1:59:47
 *  Author: 82107
 */ 


#ifndef MPU6050_H_
#define MPU6050_H_

#define MPU_ADDR1 0x68
#define MPU_ADDR2 0x69

#define SMPLRT_DIV  0x19//샘플링레이트는 어떻게 설정해야되지?
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_CONFIG2 0x1D

#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

#define PWR_MGMT_1 0x6B


#define AFS_SEL0 16384
#define AFS_SEL1 8192
#define AFS_SEL2 4096
#define AFS_SEL3 2048

#define FS_SEL0 131
#define FS_SEL1 65.5
#define FS_SEL2 32.8
#define FS_SEL3 16.4

#define PI 3.141592265359

typedef union accel_t_gyro_union{
	
	struct
	{
		uint8_t x_accel_l;
		uint8_t x_accel_h;
		uint8_t y_accel_l;
		uint8_t y_accel_h;
		uint8_t z_accel_l;
		uint8_t z_accel_h;
		
		uint8_t temperature_l;
		uint8_t temperature_h;
		
		uint8_t x_gyro_l;
		uint8_t x_gyro_h;
		uint8_t y_gyro_l;
		uint8_t y_gyro_h;
		uint8_t z_gyro_l;
		uint8_t z_gyro_h;
	}reg;

	/*uint16_t 일까 int16_t일까?? */	
	/*int16_t인 것 같다. 왜냐하면 가속도 센서 민감도가 -16g ~ +16g이므로 음수값도 취급하기 때문 */
	struct
	{
		int16_t x_accel;  
		int16_t y_accel;
		int16_t z_accel;
		
		int16_t temperature;
		
		int16_t x_gyro;
		int16_t y_gyro;
		int16_t z_gyro;
	}raw;
}accel_t_gyro;

typedef struct angle_value
{
	double roll;
	double pitch;
	double yaw;
}angle;

accel_t_gyro* Paccel_gyro_ave;

void mpu6050_write(uint8_t reg_address, uint8_t data);
void mpu6050_read(uint8_t reg_address, uint8_t len, uint8_t* buffer);
void mpu6050_init(void);
void get_accel_gyro_raw(accel_t_gyro* Paccel_gyro);
void get_roll_pitch_yaw(accel_t_gyro* Paccel_gyro, angle* Pangle);




#endif /* MPU6050_H_ */