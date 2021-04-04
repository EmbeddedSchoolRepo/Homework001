/*
 * SPI.c
 *
 * Created: 2021-02-19 오전 11:25:01
 *  Author: 82107
 */ 

#include "essential.h"
#include "mpu6050.h"

#define READ 1
#define WRITE 0


void SPI_init(void)
{	
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPOL)|(1<<CPHA)|(1<<SPR0); //mode3, 1MHz 이걸 mode3으로 해야되네?
	
	sbi(DDRB, 0); //SS
	sbi(PORTB, 1);
	
	sbi(DDRB, 1); //SCK
	sbi(DDRB, 2); //MOSI
	cbi(DDRB, 3); //MISO
	
	
}

uint8_t SPI_read(uint8_t reg_address)
{
	uint8_t data;
	
	cbi(PORTB, 0); //SS clear
	
	SPDR = (READ<<7) | reg_address;
	while(!(SPSR & (1<<SPIF)));		SPDR = 0x00; //데이터 수신을 위한 임의의 데이터 전송	while(!(SPSR & (1<<SPIF)));
	
	data = SPDR;
	
	sbi(PORTB, 0); //SS set
	
	return data;
}


void SPI_write(uint8_t reg_address, uint8_t data)
{
	cbi(PORTB, 0); //SS clear

	SPDR = (WRITE<<7) | reg_address;
	while(!(SPSR & (1<<SPIF)));		SPDR = data;	while(!(SPSR & (1<<SPIF)));
	
	sbi(PORTB, 0); //SS set
}

void mpu6050_init_SPI(void)
{
	_delay_ms(150);		// Power up time >100ms
	SPI_write(PWR_MGMT_1,0x01);
	_delay_ms(100);
	SPI_write(GYRO_CONFIG, 0x18); //-+2000bps
	SPI_write(CONFIG, 0x00);
	SPI_write(ACCEL_CONFIG, 0x18); //+=16g
	SPI_write(ACCEL_CONFIG2, 0x00); 
}

void get_accel_gyro_raw_SPI(accel_t_gyro* Paccel_gyro)
{
	uint8_t buffer[14];
	
	buffer[0] = SPI_read(ACCEL_XOUT_H);
	buffer[1] = SPI_read(ACCEL_XOUT_L);
	buffer[2] = SPI_read(ACCEL_YOUT_H);
	buffer[3] = SPI_read(ACCEL_YOUT_L);
	buffer[4] = SPI_read(ACCEL_ZOUT_H);
	buffer[5] = SPI_read(ACCEL_ZOUT_L);
	
	buffer[8] = SPI_read(GYRO_XOUT_H);
	buffer[9] = SPI_read(GYRO_XOUT_L);
	buffer[10] = SPI_read(GYRO_YOUT_H);
	buffer[11] = SPI_read(GYRO_YOUT_L);
	buffer[12] = SPI_read(GYRO_ZOUT_H);
	buffer[13] = SPI_read(GYRO_ZOUT_L);
	
	Paccel_gyro->raw.x_accel = (buffer[0] << 8) | buffer[1];
	Paccel_gyro->raw.y_accel = (buffer[2] << 8) | buffer[3];
	Paccel_gyro->raw.z_accel = (buffer[4] << 8) | buffer[5];

	Paccel_gyro->raw.x_gyro = (buffer[8] << 8) | buffer[9];
	Paccel_gyro->raw.y_gyro = (buffer[10] << 8) | buffer[11];
	Paccel_gyro->raw.z_gyro = (buffer[12] << 8) | buffer[13];
	
}

void get_accel_gyro_ave_SPI(accel_t_gyro* Paccel_gyro_ave)
{
	accel_t_gyro accel_gyro_tmep;

	double Ax_ave = 0, Ay_ave = 0, Az_ave = 0;
	double Gx_ave = 0, Gy_ave = 0, Gz_ave = 0;
	
	for(int i=0; i < 10; i++)
	{
		get_accel_gyro_raw_SPI(&accel_gyro_tmep);
		
		Ax_ave += accel_gyro_tmep.raw.x_accel;
		Ay_ave += accel_gyro_tmep.raw.y_accel;
		Az_ave += accel_gyro_tmep.raw.z_accel;
		
		Gx_ave += accel_gyro_tmep.raw.x_gyro;
		Gy_ave += accel_gyro_tmep.raw.y_gyro;
		Gz_ave += accel_gyro_tmep.raw.z_gyro;
	}
	
	Paccel_gyro_ave->raw.x_accel = (int16_t)(Ax_ave / 10);
	Paccel_gyro_ave->raw.y_accel = (int16_t)(Ay_ave / 10);
	Paccel_gyro_ave->raw.z_accel = (int16_t)(Az_ave / 10);

	Paccel_gyro_ave->raw.x_gyro = (int16_t)(Gx_ave / 10);
	Paccel_gyro_ave->raw.y_gyro = (int16_t)(Gy_ave / 10);
	Paccel_gyro_ave->raw.z_gyro = (int16_t)(Gz_ave / 10);
}

void mpu6050_run_SPI(accel_t_gyro* Paccel_gyro, accel_t_gyro* Paccel_gyro_ave, angle* Fil_angle)
{
	double Ax_tmp, Ay_tmp, Az_tmp;
	double Gx_tmp, Gy_tmp, Gz_tmp;
	double Accel_roll, Accel_pitch;
	double tmpX_angle, tmpY_angle, tmpZ_angle;

	//get Accel
	Ax_tmp = (double)(Paccel_gyro->raw.x_accel - Paccel_gyro_ave->raw.x_accel) / AFS_SEL3;
	Ay_tmp = (double)(Paccel_gyro->raw.y_accel - Paccel_gyro_ave->raw.y_accel) / AFS_SEL3;
	Az_tmp = (double)(Paccel_gyro->raw.z_accel - Paccel_gyro_ave->raw.z_accel + 2048)/ AFS_SEL3; //16348더해야돼? 더하면 값이 이상하게 나옴.-> ASF_SEL이0일떄 적용할 수 있는 거였음 ASF_SEL3이니까 2048더해주면될듯
	
	Accel_roll = atan2((-1) * Ax_tmp, sqrt(Ay_tmp*Ay_tmp + Az_tmp*Az_tmp)) * 180.0F / (double)PI;
	Accel_pitch = atan2(Ay_tmp, sqrt(Ax_tmp*Ax_tmp + Az_tmp*Az_tmp)) * 180.0F / (double)PI;
	
	//get Gyro
	Gx_tmp = (double)(Paccel_gyro->raw.x_gyro - Paccel_gyro_ave->raw.x_gyro) / FS_SEL3;
	Gy_tmp = (double)(Paccel_gyro->raw.y_gyro - Paccel_gyro_ave->raw.y_gyro) / FS_SEL3;
	Gz_tmp = (double)(Paccel_gyro->raw.z_gyro - Paccel_gyro_ave->raw.z_gyro) / FS_SEL3;
	
	
	//상보필터 적용
	tmpX_angle = Fil_angle->roll + Gx_tmp * DT;
	tmpY_angle = Fil_angle->pitch + Gy_tmp * DT;
	tmpZ_angle = Fil_angle->yaw + Gz_tmp * DT;
	
	Fil_angle->roll = ALPHA * tmpX_angle + (1.0 - ALPHA) * Accel_roll;
	Fil_angle->pitch = ALPHA * tmpY_angle + (1.0 - ALPHA) * Accel_pitch;
	Fil_angle->yaw = tmpZ_angle; //오차 누적
	//Fil_angle->yaw = ALPHA * tmpZ_angle + (1.0 - ALPHA) * Accel_yaw;    // Z축은 자이로 센서만을 이용하열 구함?
}