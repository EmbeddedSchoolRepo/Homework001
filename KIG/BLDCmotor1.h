/*
 * BLDCmotor1.h
 *
 * Created: 2021-01-18 오후 11:07:00
 *  Author: 82107
 */ 


#ifndef BLDCMOTOR1_H_
#define BLDCMOTOR1_H_

#include "Receiver.h"
#include "mpu6050.h"

#define OCR_MAX 4000
#define OCR_MIN 2000

#define CH_TO_OCR 2 + 800
#define MAX_DEGREE 45 //45도가 괜찮으려나??

#define DT_ 0.004

//#define P_gain 15
//#define I_gain 0
//#define D_gain 0

double error_rate;
//roll
double error_roll, pre_error_roll;
double Py_roll, Iy_roll, Dy_roll;
//ptich
double error_pitch, pre_error_pitch;
double Py_pitch, Iy_pitch, Dy_pitch;
//yaw
double error_yaw, pre_error_yaw;
double Py_yaw, Iy_yaw, Dy_yaw;

struct OCR_Value	//2000(1ms) ~ 4000(2ms)
{
	uint16_t LU; //Left Up		//OCR1A
	uint16_t RU; //Right Up		//OCR1B
	uint16_t RD; //Right Down	//OCR3A
	uint16_t LD; //Left Down		//OCR3B
	};

void BLDCmotor_init(void);
void ESC_Calibration(void);

uint16_t CH_to_OCR(uint16_t ch);
extern double const_dt;



void target_update(Receiver* ch, angle* target_angle);

double PID_control_roll(angle* current_value, angle* target_value, accel_t_gyro* accel_gyro);
double PID_control_pitch(angle* current_value, angle*  target_value,  accel_t_gyro* accel_gyro);
double PID_control_yaw(angle* current_value, angle*  target_value);

void motor_update(Receiver* ch, double PID_roll, double PID_pitch, double PID_yaw);

#endif /* BLDCMOTOR1_H_ */