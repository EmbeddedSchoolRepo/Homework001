/*
 * Drone_Atmega328p.c
 *
 * Created: 2021-01-12 오후 11:52:14
 * Author : phn15
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>										/* Include AVR std. library file */
#include <util/delay.h>									/* Include delay header file */
//#include <inttypes.h>									/* Include integer type header file */
#include <stdlib.h>										/* Include standard library file */
#include <stdio.h>

#include "twi.h"
#include "uart.h"
#include "MPU6050.h"


//float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;



int main(void)
{
	/* Replace with your application code */
	FILE* fpStdio = fdevopen(usartTxChar,NULL);
	
	char buffer[20], float_[10];
	float Xa,Ya,Za,t;
	float Xg=0,Yg=0,Zg=0;
	
	
	printf("---Drone Project Start---\n");
	
	UART_INIT();
	printf("uart init ok\n");
	//UART_string_transmit("uart init ok\n");
		
	i2c_init();
	printf("i2c init ok\n");
	//UART_string_transmit("i2c init ok\n");
		
	mpu6050_init();
	printf("MPU6050 reset ok\n");
	//UART_string_transmit("MPU6050 reset ok\n");
	_delay_ms(1000);
	
	while (1)
	{
		
//		Read_RawValue();
		_delay_ms(500);
		mpu6050_getRawValue();
/*     Xa = Acc_x/16384.0;					
		Ya = Acc_y/16384.0;
		Za = Acc_z/16384.0;

		Xg = Gyro_x/16.4;
		Yg = Gyro_y/16.4;
		Zg = Gyro_z/16.4;

		t = (Temperature/340.00)+36.53;					
*/
		
		//printf("Gyro X-axis = %f\n", Acc_x);
		//printf("Gyro Y-axis = %f\n", Acc_y);
		//printf("Gyro Z-axis = %f\n\n",Acc_z);
		/*
		dtostrf( Xg, 3, 2, float_ );
		sprintf(buffer," Gx = %s%c/s\t",float_,0xF8);
		UART_string_transmit(buffer);
		
		dtostrf( Yg, 3, 2, float_ );
		sprintf(buffer," Gy = %s%c/s\t",float_,0xF8);
		UART_string_transmit(buffer);
		
		dtostrf( Zg, 3, 2, float_ );
		sprintf(buffer," Gz = %s%c/s\t",float_,0xF8);
		UART_string_transmit(buffer);
		
		*/
		/*
		printf("x value : %f\n", Acc_x);
		printf("y value : %f\n", Acc_y);
		printf("z value : %f\n", Acc_z);
		
		dtostrf( Xa, 3, 2, float_ );				
		sprintf(buffer," Ax = %s g\t",float_);
		UART_string_transmit(buffer);

		dtostrf( Ya, 3, 2, float_ );
		sprintf(buffer," Ay = %s g\t",float_);
		UART_string_transmit(buffer);
			
		dtostrf( Za, 3, 2, float_ );
		sprintf(buffer," Az = %s g\t",float_);
		UART_string_transmit(buffer);

		dtostrf( t, 3, 2, float_ );
		sprintf(buffer," T = %s%cC\t",float_,0xF8);           
		UART_string_transmit(buffer);

		dtostrf( Xg, 3, 2, float_ );
		sprintf(buffer," Gx = %s%c/s\t",float_,0xF8);
		UART_string_transmit(buffer);

		dtostrf( Yg, 3, 2, float_ );
		sprintf(buffer," Gy = %s%c/s\t",float_,0xF8);
		UART_string_transmit(buffer);
			
		dtostrf( Zg, 3, 2, float_ );
		sprintf(buffer," Gz = %s%c/s\r\n",float_,0xF8);
		UART_string_transmit(buffer);
		_delay_ms(100);*/

	}
}