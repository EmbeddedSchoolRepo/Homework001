/*
 * Drone_project.c
 *
 * Created: 2020-12-21 오전 4:34:15
 * Author : 82107
 */ 
#include "essential.h"
#include "uart.h"
#include "mpu6050.h"
#include "I2C.h"
#include "MS5611.h"

int main(void)
{	
	FILE* fpStdio = fdevopen(usartTxChar, NULL);

	uart_init();
	printf("UART init\n");

	i2c_init();
	printf("I2C init\n");

	mpu6050_init();
	printf("mpu6050 init\n");
	
	accel_t_gyro accel_t_gyro6;
	angle angle3;
	
    while (1) 
    {
		get_accel_gyro_raw(&accel_t_gyro6);
		get_roll_pitch_yaw(&accel_t_gyro6, &angle3);
		
		printf("roll : %f\n", angle3.roll);
		printf("pitch : %f\n", angle3.pitch);
		
		_delay_ms(1000);
    }
}

