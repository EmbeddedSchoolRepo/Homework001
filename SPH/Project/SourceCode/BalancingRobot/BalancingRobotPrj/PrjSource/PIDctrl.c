/*
 * PIDctrl.c
 *
 * Created: 2021-01-30 오전 11:58:35
 *  Author: SON
 */ 
#include "PIDctrl.h"

//PID Gain Define
#define Kp 2
#define Ki 0.002
#define Kd 0.005
#define Ka 0

//PID reference Set 10 degree
#define ref 5.0F

static volatile double cur_err;
static volatile double pre_err;
static volatile double u;
static volatile uint8_t duty;
static volatile uint8_t dir;

void InitPIDCtrl(void)
{
	cur_err = 0.0F;
	pre_err = 0.0F;
	dir = (uint8_t)CW;
	u = 0.0F;
}

static double Cal_PID(volatile double *cur_err, volatile double *pre_err)
{
	double Pterm;
	double Iterm;
	double Dterm;
	
	Pterm = Kp * *cur_err;
	Iterm = (*pre_err + *cur_err)*dt;
	Dterm = (*pre_err - *cur_err)/dt;
	
	return Pterm+(Ki*Iterm);//+Kd*Dterm;
}

void RunPID_MotorCtrl(Angle_3Dim* AngleData)
{
	//2021.02.04 if( >= 0) => if( >= 10)
	if(AngleData->Pitch >= (double)ref)
	{
		cur_err = -1*((double)ref - AngleData->Pitch);
		dir = (uint8_t)CCW;
	}
	else
	{
		if(AngleData->Pitch >= 0) cur_err = (double)ref - AngleData->Pitch;
		else 
		{
			if((-1*AngleData->Pitch) > ref) cur_err = -1*((double)ref - (-1*AngleData->Pitch));
			else cur_err = ((double)ref - (-1*AngleData->Pitch));
		}
		
		dir = (uint8_t)CW;
	}
	
	u = Cal_PID(&cur_err, &pre_err);
	
	//Limit PID Controller Out
	if(u >= 255) u = 255;
	else u = u;
	
	if(u <= 0) u = 0;
	else u = u;
	
	
	duty = (uint8_t)((u/255)*100);
	
	#ifdef ForPIDTest
	printf("AngleData = %.2f\tRef = %.2f\tErr = %.2f\tCtrlVal = %.2f\tDuty = %d\n", AngleData->Pitch, (double)ref, cur_err, u, duty);
	#endif

	RunMotor(&duty, &dir);
	
	pre_err = cur_err;
}