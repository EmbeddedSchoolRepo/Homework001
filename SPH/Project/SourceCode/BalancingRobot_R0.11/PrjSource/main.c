/*
 * MPU6050_test.c
 *
 * Created: 2020-11-27 오전 12:08:50
 * Author : SON
 */ 
#include "PrjHeader.h"
#include "TimerCounter.h"
#include "MotorCtrl.h"
#include "PIDctrl.h"

double T;
volatile uint8_t CNT1_1ms;
volatile uint8_t CNT1_2ms;

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
	MotorStop();	
	sbi(SREG, 7);
	
	//Initialization GlobalVariable
	T = 0.0F;
	CNT1_1ms = 0;
	CNT1_2ms = 0;
	
    while (1) 
    {
			if(CNT1_1ms == 2)
			{			
				RunMPU6050();
				#ifdef ForLoopDebug
				printf("RunMPU6050 Finish\n");
				#endif
				
				Accelero_Angle = getAcceleroData(); //get Angle Value
				#ifdef ForLoopDebug
				printf("Accelero_Angle Finish\n");
				#endif				
				
				Gyro_Angle = getGyroData(); //get Angular Velocity
				#ifdef ForLoopDebug
				printf("Gyro_Angle Finish\n");
				#endif
				
				AngleData = CompleFilter(Accelero_Angle, Gyro_Angle);
				#ifdef ForLoopDebug
				printf("Filter Finish\n");
				#endif
								
				RunPID_MotorCtrl(&AngleData);
				#ifdef ForLoopDebug
				printf("PID Finish\n");
				#endif
												
				#ifdef ForPIDTest
				if(T > 1999) T = 0;
				else T = T+2;				
				printf("T = %.4f\tAngleData = %.2f\tRef = %.2f\tErr = %.2f\tCtrlVal = %.2f\tDuty = %d\n", T*(double)dt/(double)CNT1_1ms, Input, (double)ref, cur_err, u, (uint8_t)(u/256 * 100));
				#endif
			
				CNT1_1ms = 0;								
			}
			
			#ifdef ForTest
			if(CNT1_2ms == 4)
			{
				#ifdef ForTestMPU6050
				printf("Accel Pitch = %.2f\tGyro Pitch = %.2f\tFiltered Pitch = %.2f\n", Accelero_Angle->Pitch, Gyro_Angle->Pitch, AngleData.Pitch);
				#endif
				
				CNT1_2ms = 0;
			}
			#endif
			_delay_us(100);
    }
}

//Timer/Counter1 OverFlow Interrupt Period = 1ms
SIGNAL(TIMER1_OVF_vect)
{
	if(CNT1_1ms == 2) CNT1_1ms = 0;
	else CNT1_1ms++;
	//CNT1_1ms = 1;
	
	#ifdef ForTest
	CNT1_2ms++;
	#endif
	
	TCNT1H = 0xFF;
	TCNT1L = 0x82;
	cbi(TIFR1, TOV1);
}