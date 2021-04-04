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


void getDT_init(void)
{
	#if 0 // T/C0 2ms
	TCCR0 |= (1<<WGM01)|(1<<CS01)|(1<<CS02);//CTC모드, 분주비 256 -> 1계수 당 16us
	OCR0 = 124	;	//16us * 125 = 2ms
	TIMSK |= 0x02; //Output Compare Interrupt Enable
	
	//sbi(TCCR0, COM00); //toggle OC0
	//sbi(DDRB, 4); //OC0핀 출력
	#endif
	
	
	#if 1 //T/C0 4ms
	TCCR0 |= (1<<WGM01)|(1<<CS01)|(1<<CS02);//CTC모드, 분주비 256 -> 1계수 당 16us
	OCR0 = 249	;	//16us * 250 = 4ms
	TIMSK |= 0x02; //Output Compare Interrupt Enable
	
	#endif
	
	#if 0 // T/C0 500us
	TCCR0 |= (1<<WGM01) | (1<<CS02);	//CTC모드, 분주비 64 -> 1계수 당 4us
	OCR0 = 124	;	//4us * 125 = 500us
	TIMSK |= 0x02; //Output Compare Interrupt Enable
	
	//sbi(TCCR0, COM00); //toggle OC0
	//sbi(DDRB, 4); //OC0핀 출력
	#endif
	
	TIMSK |= (1<<TOIE2); //Overflow Enable
	TCCR2 |= (1<<CS20) | (1<<CS21); //64분주비 
	
	
		
	sbi(SREG, 7);
}

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
	mpu6050_write(PWR_MGMT_1,0x01); //sleep 끔, Auto selects the best available clock source ON
	_delay_ms(10);
	
	/* Sample Rate Divider -> Sample Rate = 1KHz / (1+SMPLRT_DIV) */
	//mpu6050_write(SMPLRT_DIV, 0x04);
	//mpu6050_write(SMPLRT_DIV, 0x01); //dt가 2ms 이므로 이것도 2ms로 맞춰보았다?? 맞는지는 모르겠다
	mpu6050_write(SMPLRT_DIV, 0x00);
	
	/* Gyro Configuration*/
	//mpu6050_write(GYRO_CONFIG, 0x08); //-500~ +500dps
	mpu6050_write(GYRO_CONFIG, 0x18); //-2000~ +2000dps	
	
	/* Gyro DLPF*/	
	//mpu6050_write(CONFIG, 0x00); //BW:250Hz, Delay:0.97ms
	//mpu6050_write(CONFIG, 0x02); // 92Hz, Delay : 3.9ms
	mpu6050_write(CONFIG, 0x04); //BW:20Hz Delay:9.9ms
	
	/* Accel Configuration */
	//mpu6050_write(ACCEL_CONFIG, 0x00); // -2~+2g
	mpu6050_write(ACCEL_CONFIG, 0x18); //-16~+16g
	
	/* Accel DLPF */
	//mpu6050_write(ACCEL_CONFIG2, 0x00);
	//mpu6050_write(ACCEL_CONFIG2, 0x02);
	mpu6050_write(ACCEL_CONFIG2, 0x04);
}


void get_accel_gyro_ave(accel_t_gyro* Paccel_gyro_ave)
{
	accel_t_gyro accel_gyro_tmp;

	double Ax_ave = 0, Ay_ave = 0, Az_ave = 0;
	double Gx_ave = 0, Gy_ave = 0, Gz_ave = 0;
	
	for(int i=0; i < 10; i++)
	{
		get_accel_gyro_raw(&accel_gyro_tmp);
		
		Ax_ave += accel_gyro_tmp.raw.x_accel;
		Ay_ave += accel_gyro_tmp.raw.y_accel;
		Az_ave += accel_gyro_tmp.raw.z_accel;
		
		Gx_ave += accel_gyro_tmp.raw.x_gyro;
		Gy_ave += accel_gyro_tmp.raw.y_gyro;
		Gz_ave += accel_gyro_tmp.raw.z_gyro;
	}
	
	Paccel_gyro_ave->raw.x_accel = (int16_t)(Ax_ave / 10);
	Paccel_gyro_ave->raw.y_accel = (int16_t)(Ay_ave / 10);
	Paccel_gyro_ave->raw.z_accel = (int16_t)(Az_ave / 10);

	Paccel_gyro_ave->raw.x_gyro = (int16_t)(Gx_ave / 10);
	Paccel_gyro_ave->raw.y_gyro = (int16_t)(Gy_ave / 10);
	Paccel_gyro_ave->raw.z_gyro = (int16_t)(Gz_ave / 10);
}

void get_accel_gyro_raw(accel_t_gyro* Paccel_gyro) //구조체의 값을 바꾸기 때문에 const는 쓰지 않는다. 값이 바뀌면 안되는 경우에 const를 사용하자
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

void get_Ac_roll_pitch(accel_t_gyro* Paccel_gyro, accel_t_gyro* Paccel_gyro_ave, angle* Pangle)
{
	double Ax_tmp, Ay_tmp, Az_tmp;
	
	#if 1 //오프셋 적용x
	Ax_tmp = (double)(Paccel_gyro->raw.x_accel) / AFS_SEL3;
	Ay_tmp = (double)(Paccel_gyro->raw.y_accel) / AFS_SEL3;
	Az_tmp = (double)(Paccel_gyro->raw.z_accel)/ AFS_SEL3;
	#endif
	
	#if 0 //오프셋 적용 o
	Ax_tmp = (double)(Paccel_gyro->raw.x_accel - Paccel_gyro_ave->raw.x_accel) / AFS_SEL3;
	Ay_tmp = (double)(Paccel_gyro->raw.y_accel - Paccel_gyro_ave->raw.y_accel) / AFS_SEL3;
	Az_tmp = (double)(Paccel_gyro->raw.z_accel - Paccel_gyro_ave->raw.z_accel)/ AFS_SEL3; //16348더해야돼? 더하면 값이 이상하게 나옴.-> ASF_SEL이0일떄 적용할 수 있는 거였음 ASF_SEL3이니까 2048더해주면될듯
	#endif
	
	Pangle->roll = atan2((-1) * Ax_tmp, sqrt(Ay_tmp*Ay_tmp + Az_tmp*Az_tmp)) * 180.0F / (double)PI;
	Pangle->pitch = atan2(Ay_tmp, sqrt(Ax_tmp*Ax_tmp + Az_tmp*Az_tmp)) * 180.0F / (double)PI;
	Pangle->yaw = Az_tmp;
}

void get_Gy_roll_pitch_yaw(accel_t_gyro* Paccel_gyro, accel_t_gyro* Paccel_gyro_ave, angle* Pangle)
{
	double Gx_tmp, Gy_tmp, Gz_tmp;
	
	# if 1 //오프셋 적용x
	Gx_tmp = (double)(Paccel_gyro->raw.x_gyro) / FS_SEL3;
	Gy_tmp = (double)(Paccel_gyro->raw.y_gyro) / FS_SEL3;
	Gz_tmp = (double)(Paccel_gyro->raw.z_gyro) / FS_SEL3;
	#endif
	
	#if 0 //오프셋 적용 o
	Gx_tmp = (double)(Paccel_gyro->raw.x_gyro - Paccel_gyro_ave->raw.x_gyro) / FS_SEL3;
	Gy_tmp = (double)(Paccel_gyro->raw.y_gyro - Paccel_gyro_ave->raw.y_gyro) / FS_SEL3;
	Gz_tmp = (double)(Paccel_gyro->raw.z_gyro - Paccel_gyro_ave->raw.z_gyro) / FS_SEL3;
	#endif

	Pangle->roll = Gx_tmp;
	Pangle->pitch =Gy_tmp;
	Pangle->yaw = Gz_tmp;
	
	//Pangle->roll = Gx_tmp * DT + Pangle->roll;
	//Pangle->pitch = Gy_tmp * DT + Pangle->pitch;
	//Pangle->yaw = Gz_tmp * DT + Pangle->yaw;
}

void cal_filltered_roll_pitch_yaw(angle* Ac_angle, angle* Gy_angle, angle* Fil_angle)
{
	double tmpX_angle, tmpY_angle, tmpZ_angle;
	
	//상보필터 적용
	
	tmpX_angle = Fil_angle->roll + Gy_angle->roll * DT;
	tmpY_angle = Fil_angle->pitch + Gy_angle->pitch * DT;
	tmpZ_angle = Fil_angle->yaw + Gy_angle->yaw * DT;
	
	Fil_angle->roll = ALPHA * tmpX_angle + (1.0 - ALPHA) * Ac_angle->roll;
	Fil_angle->pitch = ALPHA * tmpY_angle + (1.0 - ALPHA) * Ac_angle->pitch;
	//Fil_angle->yaw = tmpZ_angle; //오차 누적
	Fil_angle->yaw = ALPHA * tmpZ_angle + (1.0 - ALPHA) * Ac_angle->yaw;    // Z축은 자이로 센서만을 이용하열 구함?
	//Fil_angle->yaw =  atan2(sqrt(Fil_angle->roll*Fil_angle->roll + Fil_angle->pitch*Fil_angle->pitch), Fil_angle->yaw) * 180.0F / (double)PI;
	 
	 
}

void mpu6050_run(accel_t_gyro* Paccel_gyro, angle* Fil_angle)
{
	double Ax_tmp, Ay_tmp, Az_tmp;
	double Gx_tmp, Gy_tmp, Gz_tmp;
	double Accel_roll, Accel_pitch;
	double tmpX_angle, tmpY_angle, tmpZ_angle;

	//get Accel
	Ax_tmp = (double)(Paccel_gyro->raw.x_accel) / AFS_SEL3;
	Ay_tmp = (double)(Paccel_gyro->raw.y_accel) / AFS_SEL3;
	Az_tmp = (double)(Paccel_gyro->raw.z_accel)/ AFS_SEL3; //16348더해야돼? 더하면 값이 이상하게 나옴.-> ASF_SEL이0일떄 적용할 수 있는 거였음 ASF_SEL3이니까 2048더해주면될듯
	
	Accel_roll = atan2((-1) * Ax_tmp, sqrt(Ay_tmp*Ay_tmp + Az_tmp*Az_tmp)) * 180.0F / (double)PI;
	Accel_pitch = atan2(Ay_tmp, sqrt(Ax_tmp*Ax_tmp + Az_tmp*Az_tmp)) * 180.0F / (double)PI;
	
	//get Gyro
	Gx_tmp = (double)(Paccel_gyro->raw.x_gyro) / FS_SEL3;
	Gy_tmp = (double)(Paccel_gyro->raw.y_gyro) / FS_SEL3;
	Gz_tmp = (double)(Paccel_gyro->raw.z_gyro) / FS_SEL3;
	
	//상보필터 적용
	#if 1 //인터럽트 사용할 때
	tmpX_angle = Fil_angle->roll + Gx_tmp * DT;
	tmpY_angle = Fil_angle->pitch + Gy_tmp * DT;
	tmpZ_angle = Fil_angle->yaw + Gz_tmp * DT;
	#endif
	
	#if 0 //시간함수 사용할 때
	tmpX_angle = Fil_angle->roll + Gx_tmp * const_dt;
	tmpY_angle = Fil_angle->pitch + Gy_tmp * const_dt;
	tmpZ_angle = Fil_angle->yaw + Gz_tmp * const_dt;
	#endif
	
	Fil_angle->roll = ALPHA * tmpX_angle + (1.0 - ALPHA) * Accel_roll;
	Fil_angle->pitch = ALPHA * tmpY_angle + (1.0 - ALPHA) * Accel_pitch;
	Fil_angle->yaw = 0;
	//Fil_angle->yaw = tmpZ_angle; //오차 누적
	//Fil_angle->yaw = ALPHA * tmpZ_angle + (1.0 - ALPHA) * Accel_yaw;    // Z축은 자이로 센서만을 이용하열 구함?
	
}