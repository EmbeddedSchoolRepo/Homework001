/*
 * MotorCtrl.c
 *
 * Created: 2021-01-18 오후 9:46:03
 *  Author: SON
 */ 
#include "MotorCtrl.h"

#define Motor_Stop 0
#define Duty_Min 155
#define Duty_Max 255

//MotorStop Function
void MotorStop(void)
{
	//RightMotor Stop
	OCR0A = 0x00;
	OCR0B = 0x00;
	
	//LeftMotor Stop
	OCR2A = 0x00;
	OCR2B = 0x00;		
}

void MotorDir_CW(volatile uint8_t* duty)
{
	//LEFT Motor Ctrl
	OCR0A = (uint8_t)Duty_Min + *duty;
	OCR0B = (uint8_t)Motor_Stop;
		
	//RIGHT Motor Ctrl
	OCR2A = (uint8_t)Duty_Min + *duty;
	OCR2B = (uint8_t)Motor_Stop;	
}

void MotorDir_CCW(volatile uint8_t* duty)
{
	//LEFT Motor Ctrl
	OCR0B = (uint8_t)Duty_Min + *duty;
	OCR0A = (uint8_t)Motor_Stop;
	
	//RIGHT Motor Ctrl
	OCR2B = (uint8_t)Duty_Min + *duty;
	OCR2A = (uint8_t)Motor_Stop;	
}

void RunMotor(volatile uint8_t* duty, volatile uint8_t* dir)
{
	if(*dir == (uint8_t)CW) MotorDir_CW(duty);
	else MotorDir_CCW(duty);
}