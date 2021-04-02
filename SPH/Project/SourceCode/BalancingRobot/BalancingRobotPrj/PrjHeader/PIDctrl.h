/*
 * PIDctrl.h
 *
 * Created: 2021-01-30 오전 11:57:59
 *  Author: SON
 */ 


#ifndef PIDCTRL_H_
#define PIDCTRL_H_

#include "PrjHeader.h"
#include "MotorCtrl.h"
#include "Filter.h"

void InitPIDCtrl(void);
void RunPID_MotorCtrl(Angle_3Dim* AngleData);

#endif /* PIDCTRL_H_ */