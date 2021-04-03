/*
 * PIDctrl.c
 *
 * Created: 2021-01-30 오전 11:58:35
 *  Author: SON
 */ 
#include "PIDctrl.h"

//PID Gain Define
#define Kp 11.0F
#define Ki 5.0F
#define Kd 0.0F

#define Limit_Max 255
#define Limit_Min -255

#define DeadBand_Min 179.5F
#define DeadBand_Max 185.0F

//PID reference Set 10 degree
#define ref 180

float Input;
float preInput;

float cur_err;
float pre_err;

float Pterm;
float Iterm;
float Dterm;

float u;
uint8_t duty;
uint8_t dir;

void InitPIDCtrl(void)
{
	cur_err = 0.0F;
	pre_err = 0.0F;
	dir = (uint8_t)CW;
	u = 0.0F;
	
	Input = 0;
	preInput = 0;
	Pterm = 0;
	Iterm = 0;
	Dterm = 0;
}

void Cal_PID(void)
{
	float dInput = 0;
	
	cur_err = (float)ref - Input;
	dInput = Input - preInput;
	
	Pterm = (float)Kp*cur_err;
	Iterm += cur_err*(float)dt;
	Dterm = dInput/(float)dt;
	
	//if(cur_err == 0) Iterm = 0.0F;
	
	preInput = Input;
		
	u = Pterm+(float)Ki*Iterm-(float)Kd*Dterm;
}

void RunPID_MotorCtrl(Angle_3Dim* AngleData)
{
	//0도를 180으로 변환하여 연산
	Input = AngleData->Pitch+180.0;
	if(Input == (float)ref) 
	{
		Iterm = 0;
		MotorStop();
	}
	else
	{
		dir = (Input > (float)ref) ? (uint8_t)CCW : (uint8_t)CW;
		
		Cal_PID();
		
		if(u >= (float)Limit_Max) u = (float)Limit_Max;
		if(u <= (float)Limit_Min) u = (float)Limit_Min;
		
		//입력>기준값일 때 제어량은 음수이므로 양수로 변환하여 OCR값에 대입
		if(u < 0) u = -1 * u;
		
		//DeadBand 추가
		//if(Input >= (float)DeadBand_Min && Input <= (float)DeadBand_Max) u = 0;
		
		duty = (uint8_t)u;
		
		RunMotor(duty, dir);		
	}
	
} 