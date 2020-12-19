/*
 * MPU6050_test.c
 *
 * Created: 2020-11-27 오전 12:08:50
 * Author : SON
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "twi.h"
#include "MPU6050.h"

int main(void)
{
    /* Replace with your application code */
	FILE *fstdio = fdevopen(usartTxChar, NULL);
	UART_INIT();
	printf("Initiate UART Done\n");
	i2c_init();
	printf("Initiate I2C Done\n");	
	InitMPU6050();
	printf("Initiate MPU6050 Done\n");
	_delay_ms(100);
	
	pAngle_3Dim RollPitch_Result;
	
    while (1) 
    {
		RollPitch_Result = RunMPU6050();
		printf("Roll = %f\n", RollPitch_Result->Roll);
		printf("Pitch = %f\n", RollPitch_Result->Pitch);
		_delay_ms(1000);
    }
}

