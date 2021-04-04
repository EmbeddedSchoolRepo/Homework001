/*
 * MotorCtrl.h
 *
 * Created: 2021-01-18 오후 9:47:05
 *  Author: SON
 */ 


#ifndef MOTORCTRL_H_
#define MOTORCTRL_H_

#include "PrjHeader.h"
#include "TimerCounter.h"
#include "PIDctrl.h"

#define CW 1
#define CCW 0

void MotorStop(void);
void RunMotor(uint8_t duty, uint8_t dir);

#endif /* MOTORCTRL_H_ */