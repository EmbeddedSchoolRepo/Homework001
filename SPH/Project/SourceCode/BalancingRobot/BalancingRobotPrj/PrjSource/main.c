/*
 * MPU6050_test.c
 *
 * Created: 2020-11-27 오전 12:08:50
 * Author : SON
 */ 
#include "PrjHeader.h"
#include "TimerCounter.h"
#include "MotorCtrl.h"

int main(void)
{
	cbi(SREG, 7);
    /* Replace with your application code */
	FILE *fstdio = fdevopen(usartTxChar, NULL);
	InitPortSetting();
	InitTimerCounter0();
	InitTimerCounter1();
	InitTimerCounter2();
	UART_INIT();
	i2c_init();	
	InitMPU6050();
	Init_Filter();
	_delay_ms(50);
	sbi(SREG, 7);
	
	MotorStop();
	
    while (1) 
    {
    }
}


