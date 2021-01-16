/*
 * MPU6050.c
 *
 * Created: 2020-12-23 오전 1:59:36
 *  Author: 82107
 */ 
#include "essential.h"
#include "uart.h"
#include "I2C.h"
#include "mpu6050.h"

void mpu6050_write(uint8_t reg_address, uint8_t data)
{
	i2c_start();
	i2c_SLA_W(MPU_ADDR1);
	i2c_write_data(reg_address);
	i2c_write_data(data);
	i2c_stop();
}

void mpu6050_read(uint8_t reg_address, uint8_t len, uint8_t* buffer)
{
	i2c_start();
	i2c_SLA_W(MPU_ADDR1);
	i2c_write_data(reg_address);
	i2c_rep_start();
	i2c_SLA_R(MPU_ADDR1);
	
	for(int i = 0; i < (len-1); i++)
	{
		buffer[i] = i2c_readACK();
	}
	buffer[len-1] = i2c_readNACK();
	
	i2c_stop();
}


void mpu6050_init(void)
{
	_delay_ms(150);		// Power up time >100ms
	mpu6050_write(PWR_MGMT_1,0x00); //sleep 끔
	_delay_ms(1);
	//mpu6050_write(SMPLRT_DIV, 0x04);
	mpu6050_write(CONFIG, 0x04);
	mpu6050_write(GYRO_CONFIG, 0x18); //-2000~ +2000dps
	mpu6050_write(ACCEL_CONFIG, 0x18); //-16~+16g
	mpu6050_write(ACCEL_CONFIG2, 0x04);
	mpu6050_write(PWR_MGMT_1, 0x01); //초기값
	/*
	accel_t_gyro accel_t_gyro_tmep;

	double Ax_ave = 0, Ay_ave = 0, Az_ave = 0;
	double Gx_ave = 0, Gy_ave = 0, Gz_ave = 0;
	
	for(int i=0; i < 10; i++)
	{
		get_accel_gyro_raw(&accel_t_gyro_tmep);
		
		Ax_ave += accel_t_gyro_tmep.raw.x_accel;
		Ay_ave += accel_t_gyro_tmep.raw.y_accel;
		Az_ave += accel_t_gyro_tmep.raw.z_accel;
		
		Gx_ave += accel_t_gyro_tmep.raw.x_gyro;
		Gy_ave += accel_t_gyro_tmep.raw.y_gyro;
		Gz_ave += accel_t_gyro_tmep.raw.z_gyro;
	}
	
	Paccel_gyro_ave->raw.x_accel = (int16_t)(Ax_ave / 10);
	Paccel_gyro_ave->raw.y_accel = (uint16_t)(Ay_ave / 10);
	Paccel_gyro_ave->raw.z_accel = (uint16_t)(Az_ave / 10);

	Paccel_gyro_ave->raw.x_gyro = (uint16_t)(Gx_ave / 10);
	Paccel_gyro_ave->raw.y_gyro = (uint16_t)(Gy_ave / 10);
	Paccel_gyro_ave->raw.z_gyro = (uint16_t)(Gz_ave / 10);
*/

}

void get_accel_gyro_raw(accel_t_gyro* Paccel_gyro)
{
	uint8_t buffer[14];
	
	mpu6050_read(ACCEL_XOUT_H, 14, &buffer);
	
	Paccel_gyro->raw.x_accel = (buffer[0] << 8) | buffer[1];
	Paccel_gyro->raw.y_accel = (buffer[2] << 8) | buffer[3];
	Paccel_gyro->raw.z_accel = (buffer[4] << 8) | buffer[5];

	Paccel_gyro->raw.x_gyro = (buffer[8] << 8) | buffer[9];
	Paccel_gyro->raw.y_gyro = (buffer[10] << 8) | buffer[11];
	Paccel_gyro->raw.z_gyro = (buffer[12] << 8) | buffer[13];

}

void get_roll_pitch_yaw(accel_t_gyro* Paccel_gyro, angle* Pangle)
{
	double temp_x, temp_y, temp_z;
	
	
	temp_x = (double)Paccel_gyro->raw.x_accel / AFS_SEL3;
	temp_y = (double)Paccel_gyro->raw.y_accel / AFS_SEL3;
	temp_z = (double)Paccel_gyro->raw.z_accel / AFS_SEL3;
	
	/*
	//값이 더 튀는거 같은 느낌..?
	temp_x = (double)(Paccel_gyro->raw.x_accel - Paccel_gyro_ave->raw.x_accel) / AFS_SEL3;
	temp_y = (double)(Paccel_gyro->raw.y_accel - Paccel_gyro_ave->raw.y_accel) / AFS_SEL3;
	temp_z = (double)(Paccel_gyro->raw.z_accel - Paccel_gyro_ave->raw.z_accel) / AFS_SEL3;
	*/
	Pangle->roll = atan2((-1) * temp_x, sqrt(temp_y*temp_y + temp_z*temp_z)) * 180.0F / (double)PI;
	Pangle->pitch = atan2(temp_y, sqrt(temp_x*temp_x + temp_z*temp_z)) * 180.0F / (double)PI;
	Pangle->yaw = 0;
}



//보정코드 작성

//상보필터코드 작성(?)
