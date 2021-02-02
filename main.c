/*
 * Drone_Project_HN.c
 *
 * Created: 2021-01-31 오후 12:16:04
 * Author : phn15
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>										/* Include AVR std. library file */
#include <util/delay.h>									/* Include delay header file */
#include <stdlib.h>										/* Include standard library file */
#include <stdio.h>


#include "twi.h"
#include "uart.h"
#include "MPU6050.h"

int main(void)
{
	/* Replace with your application code */
	FILE* fpStdio = fdevopen(usartTxChar,NULL);
	
	UART_INIT();		
	printf("uart init ok\n");
	
	i2c_init();				//I2C 통신 for MPU6050
	printf("i2c init ok\n");

	init_MPU6050();			//자이로센서 설정
	printf("MPU6050 reset ok\n");

	//pAngle_3Dim RollPitch_Result;
	while (1)
	{
		compute_MPU6050();	//ROLL, PITCH, YAW 계산
		
		_delay_ms(1000);
	}
}

