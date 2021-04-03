/*
 * TimerCounter.h
 *
 * Created: 2020-12-29 오후 11:58:40
 *  Author: SON
 */ 


#ifndef TIMERCOUNTER_H_
#define TIMERCOUNTER_H_

#include "PrjHeader.h"
#include "MPU6050.h"
#include "Filter.h"
#include "MotorCtrl.h"
#include "PIDctrl.h"

void InitPortSetting(void);
void InitTimerCounter0(void);
void InitTimerCounter1(void);
void InitTimerCounter2(void);

volatile extern  uint8_t CNT1_1ms;
volatile extern  uint8_t CNT1_2ms;

extern pAngle_3Dim Accelero_Angle;
extern pAngle_3Dim Gyro_Angle;
extern Angle_3Dim AngleData;

#endif /* TIMERCOUNTER_H_ */