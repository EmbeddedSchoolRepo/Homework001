/*
 * key_matrix.c
 *
 * Created: 2020-11-12 오후 1:50:46
 *  Author: KKS
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "key_matrix.h"
#include "power_clock.h"
#include "uart.h"

#define sbi(RegX,bit) RegX |= (1<<bit)
#define cbi(RegX,bit) RegX &= ~(1<<bit)

static volatile bool key_status[NUM_ROW][NUM_COL] =
{
/*PORTD	 4    5    6    7     
		col0 col1 col2 col3*/
		{1,  1,  1,  1},  //row0 PORTB0 
		{1,  1,  1,  1},  //row1      1
		{1,  1,  1,  1},  //row2 PORTC1
		{1,  1,  1,  1},  //roW3      2
		{1,  1,  1,  1}   //row4      3
};

void key_io_init(void)
{
	cbi(MCUCR,PUD); //using pull-up resistor 
	
	DDRD &= ~((1<<COL0)|(1<<COL1)|(1<<COL2)|(1<<COL3));
	PORTD |= (1<<COL0)|(1<<COL1)|(1<<COL2)|(1<<COL3);
	
	DDRB |= (1<<PORTB0)|(1<<PORTB1);
	PORTB |= (1<<PORTB0)|(1<<PORTB1);
	
	DDRC |= (1<<PORTC1)|(1<<PORTC2)|(1<<PORTC3);
	PORTC |= (1<<PORTC1)|(1<<PORTC2)|(1<<PORTC3);
}

void key_int_init(void)
{
	cli();
	//sbi(PCICR,PCIE2); //Pin change interrupt 2 enable
	PCMSK2 |= (1<<PCINT23)|(1<<PCINT22)|(1<<PCINT21)|(1<<PCINT20); //DISABLE 	
	sei();
}

uint8_t key_scan(void)
{
	uint8_t j,pin_status;
	
	All_row_to_high();
	
	for(j = 0; j< NUM_ROW; j++)
	{
		switch(j)
		{
			case(0): 
				cbi(PORTB,ROW0); 
				break;
			case(1):
				sbi(PORTB,ROW0);
				cbi(PORTB,ROW1);
				break;
			case(2):
				sbi(PORTB,ROW1);
				cbi(PORTC,ROW2);
				break;
			case(3):
				sbi(PORTC,ROW2);
				cbi(PORTC,ROW3);
				break;
			case(4):
				sbi(PORTC,ROW3);
				cbi(PORTC,ROW4);
				break;
			default:
				break;
		}

		pin_status = ((PIND&HIGH_BYTE_MASK)>>4);
	//	printf("pin_status : %02x\n",pin_status);
			
		switch(pin_status)
		{
			case(14):
				key_status[j][0]=0;
				//printf("i : 0, j : %d\n",j);
				break;		
			case(13):
				key_status[j][1]=0;
			//	printf("i : 1, j : %d\n",j);
				break;			
			case(11):
				key_status[j][2]=0;
			//	printf("i : 2, j : %d\n",j);
				break;	
			case(7):
				key_status[j][3]=0;
			//	printf("i : 3, j : %d\n",j);
				break;
			default:
				break;
		}			
	}
	
	All_row_to_low();
	pin_status = ((PIND&HIGH_BYTE_MASK)>>4);
	printf("end_key_scan\n");
	printf("pint_status : %02X\n",pin_status);
	return pin_status;
}

void key_status_check(void)
{
	
	;
}

void key_send(void)
{
	;
}

void All_row_to_low(void)
{
	PORTB &= ~((1<<PORTB0)|(1<<PORTB1));
	PORTC &= ~((1<<PORTC1)|(1<<PORTC2)|(1<<PORTC3));
}

void All_row_to_high(void)
{
	PORTB |= (1<<PORTB0)|(1<<PORTB1);
	PORTC |= (1<<PORTC1)|(1<<PORTC2)|(1<<PORTC3);
}

void view_matrix(void)
{
	int i,j = 0;
	
	for(i=0;i<NUM_ROW;i++)
	{
		for(j=0;j<NUM_COL;j++)
		{
			printf("%d",key_status[i][j]);
		}
		printf("\n");
	}
}


void key_timer_init(void) //Using Timer2 for wa 
{
	cli(); //interrupt 차단
	cbi(ASSR,AS2);
	TCCR2B |= (1<<CS20)|(1<<CS21)|(1<<CS22); //PRESCALE 1024
	sbi(TCCR2A,WGM20); // CTC MODE
	//sbi(TIMSK2,OCIE2A); //TIMER COUNTER INTERRUPT ENABLE
	OCR2A = 155; //64us X 155 = 9920us = 10ms
	sei();
}

uint8_t getBit(uint8_t REGX, uint8_t i)
{
	if((REGX & (1<<i)) == 0)
	{ 
		printf("0!\n");
		return 0;
	}
	else 
	{
		printf("1!\n");
		return 1;
	}
}

void disable_pc_int(void)
{
	cbi(PCICR,PCIE2);//Disable Pin change interrupt 
	sbi(PCIFR,PCIF2);
}

void enable_pc_int(void)
{
	sbi(PCIFR,PCIF2);
	sbi(PCICR,PCIE2);//Enable Pin change interrupt
}

ISR(PCINT2_vect) //High to low interrupt occur
{
	printf("isr!\n");
	phase = 1; 
}

ISR(TIMER2_COMPA_vect)
{
	phase = 2;
	//OCR0A 값 초기화 해줘야 하는지 알아보기
}
