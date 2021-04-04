/*
 * TimerCounter.c
 *
 * Created: 2020-12-29 오후 11:57:28
 *  Author: SON
 */ 
#include "TimerCounter.h"

pAngle_3Dim Accelero_Angle;
pAngle_3Dim Gyro_Angle;
Angle_3Dim AngleData;

void InitPortSetting(void)
{
	//OC0A, OC0B Pin PWM Enable
	sbi(DDRD, PIND6);
	sbi(DDRD, PIND5);

	//OC2A, OC2B Pin PWM Enable
	sbi(DDRB, PINB3);
	sbi(DDRD, PIND3);

	//Init PORTB & PORTD
	PORTB = 0x00;
	PORTD = 0x00;
}

//Enable TimerCounter0 for Control Period
void InitTimerCounter0(void)
{
	//TimerCounter0 Interrupt Disable
	cbi(TIMSK0, TOIE0);
	cbi(TIFR0, TOV0);

	//Set TimerCounter0 OCpin Normal Operation
	//2021.01.20 Set Timer/Counter0 OCxPin Fast PWM MODE Non-Inverting Mode
	//2021.03.13 Set Timer/Counter0 OCxPin Phase correction Mode
	cbi(TCCR0A, COM0A0);
	sbi(TCCR0A, COM0A1);

	//Set TimerCounter0 OCpin Normal Operation
	//2021.01.20 Set Timer/Counter0 OCxPin Fast PWM MODE Non-Inverting Mode
	//2021.03.13 Set Timer/Counter0 OCxPin Phase correction Mode
	cbi(TCCR0A, COM0B0);
	sbi(TCCR0A, COM0B1);

	//Set TimerCounter Normal Operation
	//2021.01.20 
	//Set Timer/Counter0 Fast PWM Mode
	//2021.03.13
	//Set Timer/Counter0 Phase Correct Mode
	sbi(TCCR0A, WGM00);
	sbi(TCCR0A, WGM01);
	//cbi(TCCR0A, WGM02);

	//2021.01.20
	//Set Prescaler 8. TimerCounter CLK Source -> 16MHz/8 = 2MHz
	//2021.03.13
	//Set Prescaler 1. TimerCounter CLK source -> 16MHz
	sbi(TCCR0B, CS00);

	//2021.01.20
	//Set Motor Drive Frequency 20KHz
	//2MHz = 0.5us, 0.5us * 100 = 50us
	//TCNT+1 = 256-100 so, TCNT = 155
	//2021.02.27
	TCNT0 = 0;
	//TCNT0 = 255;

	//2021.01.20
	//Non-Inverting Mode, OCn Pin is 'LOW' @ OCRxA < Counter Value
	//Non-Inverting Mode, OCn Pin is 'LOW' @ OCRxB > Counter Value
	OCR0A = 0x00;
	OCR0B = 0x00;
}

//Enable TimerCounter1 for Motor Drive
void InitTimerCounter1(void)
{
	//Enable Timer/Counter1 Overflow Interrupt
	cbi(TIMSK1, TOIE1);
	cbi(TIFR1, TOV1);

	//Set Normal Port Mode
	cbi(TCCR1A, COM1A0);
	cbi(TCCR1A, COM1A1);
	cbi(TCCR1A, COM1B0);
	cbi(TCCR1A, COM1B1);

	//Fast PWM, TOV on TOP, Updata OCR1x pin on Bottom, Counter Top Value = ICR1
	//2020.01.20 
	//Normal Mode
	cbi(TCCR1A, WGM10);
	cbi(TCCR1A, WGM11);
	cbi(TCCR1B, WGM12);
	cbi(TCCR1B, WGM13);

	//Clock Source = System Clock/8 = 16000000/8 = 2MHz
	//2020.01.20 
	//System Clock / 64 = 16000000/64 = 250KHz = 4us
	sbi(TCCR1B, CS10);
	sbi(TCCR1B, CS11);
	//sbi(TCCR1B, CS12);

	//Timer/Counter1 CLK Period = 4us
	//TCNT1 = 65410, Timer Interrupt Period = 4us*65410 = 500us
	//TCNT1 = 0xFF82;
	TCNT1H = 0xFF;
	TCNT1L = 0x82;

	//2021.01.20
	//TimerCounter1 OVF Interrupt Enable
	sbi(TIMSK1, TOIE1);
	//sbi(TIFR1, TOV1);	
}

//Enable TimerCounter2 for Motor Drive
void InitTimerCounter2(void)
{
	//Disable Timer/Counter2 Overflow Interrupt
	cbi(TIMSK2, TOIE2);
	cbi(TIFR2, TOV2);

	//Set Fast PWM Mode, Non-Inverting Mode
	//2021.03.13 Set Timer/Counter0 OCxPin Phase correction Mode	
	cbi(TCCR2A, COM2A0);
	sbi(TCCR2A, COM2A1);

	//Set Fast PWM Mode, Non-Inverting Mode
	//2021.03.13 Set Timer/Counter0 OCxPin Phase correction Mode
	cbi(TCCR2A, COM2B0);
	sbi(TCCR2A, COM2B1);

	//Fast PWM, TOV on MAX, Updata OCR1x pin on Bottom, Counter Top Value = 0xFF
	//2021.03.13
	//Set Timer/Counter0 Phase Correct Mode
	sbi(TCCR2A, WGM20);
	sbi(TCCR2A, WGM21);
	//cbi(TCCR2B, WGM22);

	//Clock Source = System Clock/8 = 16000000/8 = 2MHz
	//2021.03.13
	//Set Prescaler 1. TimerCounter CLK source -> 16MHz
	sbi(TCCR2B, CS20);

	//Set Motor Drive Frequency 20KHz
	//2MHz = 0.5us, 0.5us * 100 = 50us
	//TCNT+1 = 256-100 so, TCNT = 155
	//2021.02.27
	TCNT2 = 0;
	//TCNT2 = 255;

	//OC2x Pin Duty 0% => Motor Stop
	OCR2A = 0x00;
	OCR2B = 0x00;
}