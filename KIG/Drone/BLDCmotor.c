/*
 * BLDCmotor.c
 *
 * Created: 2020-12-27 오전 2:44:24
 *  Author: 82107
 */ 

#include "essential.h"
#include "BLDCmotor1.h"
#include "mpu6050.h"

extern double Pgain_roll;
extern double Igain_roll;
extern double Dgain_roll;
extern double Pgain_roll_outer;

extern double Pgain_pitch;
extern double Igain_pitch;
extern double Dgain_pitch;
extern double Pgain_pitch_outer;

extern double Pgain_yaw;
extern double Igain_yaw;
extern double Dgain_yaw;
extern double Pgain_yaw_outer;

void ESC_Calibration(void)
{
	//sbi(DDRD, 7); //확인용 LED
	//
	//_delay_ms(1000);
	//
	//OCR0A = OCR_MAX;
	//OCR0B = OCR_MAX;
	//OCR2A = OCR_MAX;
	//OCR2B = OCR_MAX;
	//
	//sbi(PORTD, 7); //LED가 켜지면 배터리를 연결.
	//_delay_ms(3000);
	//cbi(PORTD, 7); //LED가 꺼지기 전까지 배터리를 연결해야됨
	//_delay_ms(3000);
	//OCR0A = OCR_MIN;
	//OCR0B = OCR_MIN;
	//OCR2A = OCR_MIN;
	//OCR2B = OCR_MIN;
	
}

void BLDCmotor_init(void)
{
	/*Timer/Counter1 setting*/
	TCCR1A = 0xA2; //펄스모양은 High Level 먼저, Fast PWM모드(ICR설정)
	TCCR1B = 0x1A; //분주비8
	TCCR1C = 0xC0; //OC1A, OC1B 채널 사용
	sbi(DDRB, 5); //PB5, PB6출력
	sbi(DDRB, 6);
	ICR1 = 39999; //20ms
	
	OCR1A = OCR_MIN;
	OCR1B = OCR_MIN;
	
	//TIMSK는 테스트 용도
	//sbi(TIMSK, TOIE1);
	
	/*Timer/Counter3 setting*/
	TCCR3A = 0xA2;
	TCCR3B = 0x1A;
	TCCR3C = 0xC0; //OC3A, OC3B 채널 사용
	sbi(DDRE, 3); //PE3, PE4출력
	sbi(DDRE, 4);
	ICR3 = 39999; //20ms
	
	OCR3A = OCR_MIN;
	OCR3B = OCR_MIN;
	
	//TIMSK는 테스트 용도
	//sbi(ETIMSK, TOIE3);
	
	sbi(SREG, 7);
}


void target_update(Receiver* ch, angle* target_angle)
{
	//channel to degree
	target_angle->roll = ((double)ch->ch1 - 1100) * MAX_DEGREE / 500;
	
	target_angle->pitch = -((double)ch->ch2 - 1100) * MAX_DEGREE / 500;
	
	//target_angle->yaw = ((double)ch->ch4 - 1100) * MAX_DEGREE / 500;
}

double PID_control_roll(angle* current_value, angle* target_value, accel_t_gyro* accel_gyro)
{
	static double PID;
	
	double Gx = (double)(accel_gyro->raw.x_gyro) / FS_SEL3;
	
	error_roll = current_value->roll - target_value->roll;
	error_rate = (error_roll * Pgain_roll_outer) - Gx;
	
	Py_roll = error_rate;
	Iy_roll = Iy_roll + error_rate * DT_;
	Dy_roll =  (error_rate - pre_error_roll) / DT_;

	PID = (Pgain_roll * Py_roll) + (Igain_roll * Iy_roll) + (Dgain_roll * Dy_roll);

	pre_error_roll = error_roll;
	
	return PID;
	
	//static double PID;
//
	//
	//error_roll = current_value->roll - target_value->roll;
	//
	//Py_roll = error_roll;
	//Iy_roll = Iy_roll + error_roll * DT_;
	//Dy_roll =  (error_roll - pre_error_roll) / DT_;
	//
	//PID = (Pgain_roll * Py_roll) + (Igain_roll * Iy_roll) + (Dgain_roll * Dy_roll);
	//
	//pre_error_roll = error_roll;
	//
	//return PID;
}


double PID_control_pitch(angle* current_value, angle*  target_value,  accel_t_gyro* accel_gyro)
{
	static double PID;
	
	double Gy = (double)(accel_gyro->raw.y_gyro) / FS_SEL3;
	
	error_pitch = current_value->pitch - target_value->pitch;
	error_rate = (error_pitch * Pgain_pitch_outer) - Gy;
	
	Py_pitch = error_rate;
	Iy_pitch = Iy_pitch + error_rate * DT_;
	Dy_pitch =  (error_rate - pre_error_pitch) / DT_;

	PID = (Pgain_pitch * Py_pitch) + (Igain_pitch * Iy_pitch) + (Dgain_pitch * Dy_pitch);

	pre_error_pitch = error_pitch;
	
	return PID;
	
	//static double PID;
	//
	//error_pitch = current_value->pitch - target_value->pitch;
	//
	//Py_pitch = error_pitch;
	//Iy_pitch = Iy_pitch + error_pitch * DT_;
	//Dy_pitch =  (error_pitch - pre_error_pitch) / DT_;
	//
	//PID = (Pgain_roll * Py_roll) + (Igain_roll * Iy_roll) + (Dgain_roll * Dy_roll);
	//
	//pre_error_roll = error_roll;
	//
	//return PID;
}

double PID_control_yaw(angle* current_value, angle*  target_value)
{
	static double PID;
	
	error_yaw = current_value->yaw - target_value->yaw;

	Py_yaw = error_yaw;
	Iy_yaw = Iy_yaw + error_yaw* DT_;
	Dy_yaw =  (error_yaw - pre_error_yaw) / DT_;

	PID = (Pgain_roll * Py_yaw) + (Igain_roll * Iy_yaw) + (Dgain_roll * Dy_yaw);

	pre_error_yaw = error_yaw;
	
	return 0;//일단은 0으로 고정시켜놓자
}


void motor_update(Receiver* ch, double PID_roll, double PID_pitch, double PID_yaw)
{	
	//PID 최대 최소 제한 -2000~2000?맞나?
	if(PID_roll < -2000)
		PID_roll = -2000;
	else if(PID_roll > 2000)
		PID_roll = 2000;
	
	if(PID_pitch < -2000)
		PID_pitch = -2000;
	else if(PID_pitch > 2000)
		PID_pitch = 2000;
	
	if(PID_yaw < -2000)
		PID_yaw = -2000;
	else if(PID_yaw > 2000)
		PID_yaw = 2000;
	
	if(ch->ch3 < 650)
	{
		OCR1A = 2000;
		
		OCR1B = 2000;
		
		OCR3A = 2000;
		
		OCR3B = 2000;
	}
	else{
		OCR1A = -PID_roll - PID_pitch - PID_yaw + (ch->ch3 * CH_TO_OCR); 
		
		OCR1B = PID_roll - PID_pitch + PID_yaw + (ch->ch3 * CH_TO_OCR);
		//OCR1B = 2000;
		
		OCR3A = PID_roll + PID_pitch - PID_yaw + (ch->ch3 * CH_TO_OCR);
		
		OCR3B = -PID_roll + PID_pitch + PID_yaw + (ch->ch3 * CH_TO_OCR);
		//OCR3B = 2000;
	}
	
	//OCR값 최대 최소 제한
	if(OCR1A > 4000)
		OCR1A = 4000;
	else if (OCR1A < 2000)
		OCR1A = 2000;
		
	if(OCR1B > 4000)
		OCR1B = 4000;
	else if (OCR1B < 2000)
		OCR1B = 2000;
	
	if(OCR3A > 4000)
		OCR3A = 4000;
	else if (OCR3A < 2000)
		OCR3A = 2000;
	
	if(OCR1B > 4000)
		OCR1B = 4000;
	else if (OCR1B < 2000)
		OCR1B = 2000;
		
		
	
}
