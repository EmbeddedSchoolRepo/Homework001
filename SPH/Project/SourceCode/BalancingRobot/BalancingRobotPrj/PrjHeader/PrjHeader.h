/*
 * PrjHeader.h
 *
 * Created: 2020-12-30 오전 12:01:50
 *  Author: SON
 */ 

#ifndef PRJHEADER_H_
#define PRJHEADER_H_

#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/************************************************************************/
/*                          USER Definition                             */
/************************************************************************/
#define ENABLE 1
#define DISABLE 0
#define I2C_WRITE   0
#define I2C_READ   1

#define sbi(PORTX, BitX) (PORTX |= (1<<BitX))
#define cbi(PORTX, BitX) (PORTX &= ~(1<<BitX))

//#define ForTest 1
//#define ForTestMPU6050 2
//#define ForPIDTest 3

#define Filter_EN 1
#define dt 0.001F//TimerInterrupt1 Period = 1ms = Control Period

/************************************************************************/
/*                     Angle Structure Definition                       */
/************************************************************************/
typedef struct
{
	double Roll;
	double Pitch;
	double Yaw;
}Angle_3Dim;

typedef Angle_3Dim* pAngle_3Dim;

#endif /* PRJHEADER_H_ */