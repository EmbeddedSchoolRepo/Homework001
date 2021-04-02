/*
 * Filter.h
 *
 * Created: 2021-01-11 오후 8:15:27
 *  Author: SON
 */ 


#ifndef FILTER_H_
#define FILTER_H_

#include "PrjHeader.h"
#include "MPU6050.h"

Angle_3Dim CompleFilter(pAngle_3Dim AccelAngle, pAngle_3Dim GyroAngle);
void Init_Filter(void);

#endif /* FILTER_H_ */