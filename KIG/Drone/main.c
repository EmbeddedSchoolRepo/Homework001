/*
 * DroneProgect_ATmega128.c
 *
 * Created: 2021-01-28 오후 1:18:32
 * Author : 82107
 */ 
#include "essential.h"
#include "uart.h"
#include "mpu6050.h"
#include "I2C.h"
#include "Receiver.h"
#include "BLDCmotor1.h"
#include "SPI.h"

//		MPU6050			//
accel_t_gyro accel_gyro_ave;
accel_t_gyro accel_gyro;
angle Ac_angle = {0, 0, 0};
angle Gy_angle = {0, 0, 0};
angle Fil_angle = {0, 0, 0};
volatile uint8_t MPU_flag = 0;

//		수신기			//
Receiver channel;
uint16_t duty;
uint16_t t1, t2;
uint8_t rising_cnt = 0;
uint8_t falling_cnt = 0;

//		PID		//
angle target_angle;
double PID_roll, PID_pitch, PID_yaw;

double Pgain_roll = 3;
double Igain_roll = 0;
double Dgain_roll = 0;
double Pgain_roll_outer = 0;

double Pgain_pitch = 0;
double Igain_pitch = 0;
double Dgain_pitch = 0;
double Pgain_pitch_outer = 0;

double Pgain_yaw = 0;
double Igain_yaw = 0;
double Dgain_yaw = 0;
double Pgain_yaw_outer = 0;

uint8_t P_flag = 0;
uint8_t I_flag = 0;
uint8_t D_flag = 0;

//		시간		//
unsigned long long timer2_overflow_count = 0;
unsigned long long t_new = 0, t_old = 0;
int dt = 0;
int count = 0;
int dt_flag = 0;
double const_dt = 0.01;

unsigned long long micros(void)	//작동시간 반환 함수(잘 작동 안되는 듯)
{
	unsigned long long m;
	uint8_t oldSREG = SREG;
	uint8_t t;
	
	cbi(SREG,7);
	m = timer2_overflow_count;
	t = TCNT2;
	
	if ((TIFR & (1<<TOV2)) && (t < 255))
	{
		m++;
	}
	
	SREG = oldSREG;
	
	return ((m * 256) + t) * 4; //(분주비64/(16*1,000,000)
}

int main(void)
{
	FILE* fpStdio = fdevopen(usartTxChar, NULL);
	
	uart_init();
	printf("UART init\n");

	#if 1	//I2C
	i2c_init();
	printf("I2C init\n");

	mpu6050_init();
	printf("mpu6050 init\n");
	
	get_accel_gyro_ave(&accel_gyro_ave);
	
	//printf("x : %d  y : %d  z : %d\n", accel_gyro_ave.raw.x_accel, accel_gyro_ave.raw.y_accel, accel_gyro_ave.raw.z_accel);
	#endif
	
	
	#if 0	//SPI
	SPI_init();
	printf("SPI init\n");
	
	mpu6050_init_SPI();
	printf("mpu6050 SPI init\n");
	
	get_accel_gyro_ave_SPI(&accel_gyro_ave);
	#endif
	
	BLDCmotor_init();
	printf("BLDCmotor init\n");
	
	Receiver_init();
	printf("Rceiver init\n");
	
	getDT_init(); 
	printf("getDT init\n");
	
    while (1) 
    {	
		
		
#if 1 //인터럽트 플래그 사용
		
 		if(MPU_flag == 1)
 		{
	 		cbi(TIMSK,OCIE0);
	 		
	 		get_accel_gyro_raw(&accel_gyro);
	 		mpu6050_run(&accel_gyro, &Fil_angle);
	 		
	 		MPU_flag = 0;
	 		
	 		sbi(TIMSK,OCIE0);
 		}
		 
		 target_update(&channel, &target_angle);
		 
		 PID_roll = PID_control_roll(&Fil_angle, &target_angle, &accel_gyro);
		 PID_pitch = PID_control_pitch(&Fil_angle, &target_angle, &accel_gyro);
		 PID_yaw = PID_control_yaw(&Fil_angle, &target_angle);
		 
		 motor_update(&channel, PID_roll, PID_pitch, PID_yaw);
		 
		 //printf("roll : %f\n", Fil_angle.roll);
		 
		 //int a = OCR1A;
		 //int b = OCR1B;
		 //int c = OCR3A;
		 //int d = OCR3B;
		 //
		 //printf("roll_current : %f  roll_target : %f  a:%d  b:%d  c:%d  d:%d\n", Fil_angle.roll, target_angle.roll, a, b, c, d);
 #endif
		
		
#if 0	//시간 함수 사용한 경우
		
		get_accel_gyro_raw(&accel_gyro);
		
		//if(dt_flag < 10)
		//{
			//t_new = micros();
			//dt = (int)(t_new - t_old);
			//count = count + 1;
			////printf("time : %d(us)   count : %d\n", dt, count);
			//t_old = t_new;
			//
			//const_dt = (double)dt * us_to_s;
			//
			//
			//dt_flag++;
		//}

		t_new = micros();
		dt = (int)(t_new - t_old);
		count = count + 1;
		printf("time : %d(us)   count : %d\n", dt, count);
		t_old = t_new;

		const_dt = (double)dt * us_to_s;
		
		
		mpu6050_run(&accel_gyro, &Fil_angle);
		target_update(&channel, &target_angle);
		
		PID_roll = PID_control_roll(&Fil_angle, &target_angle);
		PID_pitch = PID_control_pitch(&Fil_angle, &target_angle);
		PID_yaw = PID_control_yaw(&Fil_angle, &target_angle);
		
		motor_update(&channel, PID_roll, PID_pitch, PID_yaw);
		
		//printf("roll : %f\n", Fil_angle.roll);
		
		//printf("P_gain : %f   I_gain : %f\n", P_gain, I_gain);
				
		
		
		//printf("pitch_current : %f pitch_target : %f  a:%d  b:%d  c:%d  d:%d  || P_gain : %d\n", Fil_angle.pitch, target_angle.pitch, a, b, c, d, P_gain);
#endif	
		
#if 0 //DLPF만 사용한 경우
		get_accel_gyro_raw(&accel_gyro);
		get_Ac_roll_pitch(&accel_gyro, &accel_gyro_ave, &Ac_angle);
		
		target_update(&channel, &target_angle);
		
		PID_roll = PID_control_roll(&Ac_angle, &target_angle);
		PID_pitch = PID_control_pitch(&Ac_angle, &target_angle);
		PID_yaw = PID_control_yaw(&Ac_angle, &target_angle);
		
		motor_update(&channel, PID_roll, PID_pitch, PID_yaw);
		
		//printf("roll : %f\n", Ac_angle.roll);
			
		//int a = OCR1A;
		//int b = OCR1B;
		//int c = OCR3A;
		//int d = OCR3B;
		//printf("a:%d  b:%d  c:%d  d:%d\n", a, b, c, d);	
		
#endif	
		
				
		if(channel.ch6 > 550 && channel.ch6 < 650 && P_flag == 1)
		{
			Pgain_roll = Pgain_roll + 1;
			P_flag = 0;
		}
		
		if(channel.ch6 > 1550 && channel.ch6 < 1650 && P_flag == 0)
		{
			Pgain_roll = Pgain_roll + 1;
			P_flag = 1;
		}
		
		if(channel.ch5 > 550 && channel.ch5 < 650 && I_flag == 1)
		{
			Pgain_roll_outer = Pgain_roll_outer + 1;
			I_flag = 0;
		}
		
		if(channel.ch5 > 1550 && channel.ch5 < 1650 && I_flag == 0)
		{
			Pgain_roll_outer = Pgain_roll_outer + 1;
			I_flag = 1;
		}
		
		
		//if(channel.ch6 > 550 && channel.ch6 < 650 && D_flag == 1)
		//{
			//D_gain = D_gain + 0.1;
			//D_flag = 0;
		//}
		//
		//if(channel.ch6 > 1550 && channel.ch6 < 1650 && D_flag == 0)
		//{
			//D_gain = D_gain + 0.1;
			//D_flag = 1;
		//}
    }
	
	
	
}
ISR (TIMER2_OVF_vect) //4us * 256
{
	timer2_overflow_count++;	
}


/************************************************************************/
/* MPU6050 인터럽트(2ms)                                                 */
/************************************************************************/
ISR (TIMER0_COMP_vect)
{
// 	#if 0	//SPI
// 	get_accel_gyro_raw_SPI(&accel_gyro);
// 	mpu6050_run_SPI(&accel_gyro, &accel_gyro_ave, &Fil_angle);
// 	#endif
// 	
// 	#if 0	//I2C
// 	get_accel_gyro_raw(&accel_gyro);
// 	get_Ac_roll_pitch(&accel_gyro, &accel_gyro_ave, &Ac_angle);
// 	get_Gy_roll_pitch_yaw(&accel_gyro, &accel_gyro_ave, &Gy_angle);
// 	cal_filltered_roll_pitch_yaw(&Ac_angle, &Gy_angle, &Fil_angle);
// 	#endif
	
	
	//get_accel_gyro_raw(&accel_gyro);
	//mpu6050_run(&accel_gyro, &Fil_angle);
	
	//t_new = micros();
	//dt = (int)(t_new - t_old);
	//count = count + 1;
	//printf("time : %d(us)   count : %d\n", dt, count);
	//t_old = t_new;
	
	
	#if 1
	MPU_flag=1;
	#endif
}

/************************************************************************/
/* 수신기 인터럽트                                                       */
/************************************************************************/

ISR (INT7_vect)
{
	if(EICRB == 0xC0) //rising edge이면
	{
		t1 = TCNT1;
		
		EICRB = 0x80;  //falling edge ON
		sbi(EIFR, INTF7); 
		
		rising_cnt++;
	}
	else//falling edge이면
	{
		t2 = TCNT1;
		
		falling_cnt++;
		
		//시간 계산(us단위)
		if(t1 > t2)
		{
			duty = 39999 - t1 + t2;
		}
		else
		{
			duty = t2 - t1;
		}
		
		duty = duty * COUNT_s * s_to_us;
		
		EICRB = 0xC0;  //rising edge ON
		sbi(EIFR, INTF7);
		
	}
	
	//채널이 밀리지 않고 파싱되게끔 해주는 코드
	if(duty > 4000) //마지막 잉여 채널은 4600~10500us 범위를 가짐
	{
		rising_cnt = 9;
		falling_cnt = 9;
	}

	//channel 할당
	switch(rising_cnt + falling_cnt) //업, 다운 한 번씩 발생할 때마다 주기를 파싱
	{
		case 2:
		channel.ch1 = duty;
		break;
		case 4:
		channel.ch2 = duty;
		break;
		case 6:
		channel.ch3 = duty;
		break;
		case 8:
		channel.ch4 = duty;
		break;
		case 10:
		channel.ch5 = duty;
		break;
		case 12:
		channel.ch6 = duty;
		break;
		case 14:
		channel.ch7 = duty;
		break;
		case 16:
		channel.ch8 = duty;
		break;
		case 18: //
		channel.remainder_value = duty;
		falling_cnt = 0;
		rising_cnt = 0;
		default:
		//
		break;
	}
	
}


//	PWM파형으로 파싱받는 코드
/*
ISR (INT2_vect)
{
	if(EICRA & (1<<ISC20)) //rising edge이면
	{
		t1 = TCNT1;
		
		cbi(EICRA, ISC20);  //falling edge ON
		
		sbi(EIFR, INTF2);
		
	}
	else if((EICRA & (1<<ISC20)) == 0)//falling edge이면
	{
		t2 = TCNT1;
		
		//시간 계산(us단위)
		if(t1 > t2)
		{
			duty = 39999 - t1 + t2;
		}
		else
		{
			duty = t2 - t1;
		}
		
		duty = duty * COUNT_s * s_to_us;
		
		sbi(EICRA, ISC20);  //rising edge ON
		
		sbi(EIFR, INTF2);
		
		channel.ch1 = duty;
	}
	
}

ISR (INT3_vect)
{
	if(EICRA & (1<<ISC30)) //rising edge이면
	{
		t1 = TCNT1;
		
		cbi(EICRA, ISC30);  //falling edge ON
		
		sbi(EIFR, INTF3);
		
	}
	else if((EICRA & (1<<ISC30)) == 0)//falling edge이면
	{
		t2 = TCNT1;
		
		//시간 계산(us단위)
		if(t1 > t2)
		{
			duty = 39999 - t1 + t2;
		}
		else
		{
			duty = t2 - t1;
		}
		
		duty = duty * COUNT_s * s_to_us;
		
		sbi(EICRA, ISC30);  //rising edge ON
		
		sbi(EIFR, INTF3);
		
		channel.ch2 = duty;
	}
	
}

ISR (INT5_vect)
{
	if(EICRB & (1<<ISC50)) //rising edge이면
	{
		t1 = TCNT1;
		
		cbi(EICRB, ISC50);  //falling edge ON
		
		sbi(EIFR, INTF5);
		
	}
	else if((EICRB & (1<<ISC50)) == 0)//falling edge이면
	{
		t2 = TCNT1;
		
		//시간 계산(us단위)
		if(t1 > t2)
		{
			duty = 39999 - t1 + t2;
		}
		else
		{
			duty = t2 - t1;
		}
		
		duty = duty * COUNT_s * s_to_us;
		
		sbi(EICRB, ISC50);  //rising edge ON
		
		sbi(EIFR, INTF5);
		
		channel.ch3 = duty;
	}
}

ISR (INT6_vect)
{
	if(EICRB & (1<<ISC60)) //rising edge이면
	{
		t1 = TCNT1;
		
		cbi(EICRB, ISC60);  //falling edge ON
		
		sbi(EIFR, INTF6);
		
	}
	else if((EICRB & (1<<ISC60)) == 0)//falling edge이면
	{
		t2 = TCNT1;
		
		//시간 계산(us단위)
		if(t1 > t2)
		{
			duty = 39999 - t1 + t2;
		}
		else
		{
			duty = t2 - t1;
		}
		
		duty = duty * COUNT_s * s_to_us;
		
		sbi(EICRB, ISC60);  //rising edge ON
		
		sbi(EIFR, INTF6);
		
		channel.ch4 = duty;
	}
}
*/