/*
 * PIDctrl.c
 *
 * Created: 2021-01-30 오전 11:58:35
 *  Author: SON
 */ 
#include "PIDctrl.h"

//PID Gain Define
#define Kp 10
#define Ki 0
#define Kd 0
#define Ka 0

//PID reference Set 10 degree
#define ref 0.0F

static volatile double err;
static volatile double pre_err;
static volatile	double Pterm;
static volatile	double Iterm;
static volatile double preIterm;
static volatile	double Dterm;
	
static volatile double u;
static volatile uint8_t duty;
static volatile uint8_t dir;

void InitPIDCtrl(void)
{
	err = 0.0F;
	pre_err = 0.0F;
	dir = (uint8_t)CW;
	u = 0.0F;
	Pterm = 0.0F;
	Iterm = 0.0F;
	Dterm = 0.0F;
	preIterm = 0.0F;
}

static double Cal_PID(void)
{	
	Pterm = Kp * err;
	Iterm = preIterm + err;
	Dterm = err - pre_err;
	
	preIterm = Iterm;
	pre_err = err;
	
	return Pterm+(Ki*Iterm)+Kd*Dterm;
}

void RunPID_MotorCtrl(Angle_3Dim* AngleData)
{
	//2021.02.04 if( >= 0) => if( >= 10)
	if(AngleData->Pitch > (double)ref)
	{
		err = -1*((double)ref - AngleData->Pitch);
		dir = (uint8_t)CCW;
	}
	else
	{
		if(AngleData->Pitch >= 0) err = (double)ref - AngleData->Pitch;
		else 
		{
			if((-1*AngleData->Pitch) > ref) err = -1*((double)ref - (-1*AngleData->Pitch));
			else err = ((double)ref - (-1*AngleData->Pitch));
		}
		
		dir = (uint8_t)CW;
	}
	
	u = Cal_PID();
	
	//Limit PID Controller Out
	if(u > 255) u = 245;

	if(u < 0) u = 0;
	
	
	duty = (uint8_t)((u/255)*100);
	
	#ifdef ForPIDTest
	printf("AngleData = %.2f\tRef = %.2f\tErr = %.2f\tCtrlVal = %.2f\tDuty = %d\tDir=%d\n", AngleData->Pitch, (double)ref, cur_err, u, duty, dir);
	#endif

	RunMotor(&duty, &dir);
}