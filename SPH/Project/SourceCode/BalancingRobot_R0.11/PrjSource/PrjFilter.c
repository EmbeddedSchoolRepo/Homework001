/*
 * PrjFilter.c
 *
 * Created: 2021-01-09 오전 9:33:55
 *  Author: SON
 */ 

#include "Filter.h"

//#define dt 0.001F //Ts
//#define alpha 0.1659324 //alpha = tau/(tau+Ts) @fc(cut-off Frequency) = 100Hz

//2021.01.20
//Set Sampling Time = 1ms
//#define alpha 0.6141304F//tau = 1/(2*pi*fc), Ts = 1ms, alpha = tau/(tau+Ts)

//2021.03.06
//Set Sampling Time = 500us
//#define alpha 0.760942776

//2021.03.16
//fc = 2KHz
#define alpha 0.073711F

//2021.03.16
//fc = 2KHz
//@500us
//#define alpha 0.137302F

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
	Filter_Angle.Roll = (1.0F-(float)alpha)*AccelAngle->Roll + (float)alpha*(preFilter_Angle.Roll + (float)dt * GyroAngle->Roll);
	Filter_Angle.Pitch = (1.0F-(float)alpha)*AccelAngle->Pitch + (float)alpha*(preFilter_Angle.Pitch + (float)dt * GyroAngle->Pitch);
	Filter_Angle.Yaw = (1.0F-(float)alpha)*AccelAngle->Yaw + (float)alpha*(preFilter_Angle.Yaw + (float)dt * GyroAngle->Yaw);

	preFilter_Angle = Filter_Angle;

	return Filter_Angle;
} 