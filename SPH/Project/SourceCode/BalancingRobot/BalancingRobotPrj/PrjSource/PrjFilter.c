/*
 * PrjFilter.c
 *
 * Created: 2021-01-09 오전 9:33:55
 *  Author: SON
 */ 

#include "Filter.h"

#define dt 0.001F //Ts
//#define alpha 0.1659324 //alpha = tau/(tau+Ts) @fc(cut-off Frequency) = 100Hz

//2021.01.20
//Set Sampling Time = 1ms
#define alpha 0.6141304//tau = 1/(2*pi*fc), Ts = 1ms, alpha = tau/(tau+Ts)

static Angle_3Dim Filter_Angle;
static Angle_3Dim preFilter_Angle;

void Init_Filter(void)
{
	Filter_Angle.Roll = 0.0F;
	Filter_Angle.Pitch = 0.0F;
	Filter_Angle.Yaw = 0.0F;
	
	preFilter_Angle.Roll = 0.0F;
	preFilter_Angle.Pitch = 0.0F;
	preFilter_Angle.Yaw = 0.0F;
}

//Complementary Filter
//Filter Cut-off Frequency 100Hz
//Sampling Period 8ms
//2021.01.21
//Sampling Period 1ms
Angle_3Dim CompleFilter(pAngle_3Dim AccelAngle, pAngle_3Dim GyroAngle)
{	
	Filter_Angle.Roll = (1.0F-(double)alpha)*AccelAngle->Roll + (double)alpha*(preFilter_Angle.Roll + (double)dt * GyroAngle->Roll);
	Filter_Angle.Pitch = (1.0F-(double)alpha)*AccelAngle->Pitch + (double)alpha*(preFilter_Angle.Pitch + (double)dt * GyroAngle->Pitch);
	Filter_Angle.Yaw = (1.0F-(double)alpha)*AccelAngle->Yaw + (double)alpha*(preFilter_Angle.Yaw + (double)dt * GyroAngle->Yaw);
	
	preFilter_Angle = Filter_Angle;
	
	return Filter_Angle;
}