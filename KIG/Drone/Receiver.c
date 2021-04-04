/*
 * Receiver.c
 *
 * Created: 2021-01-16 오후 2:03:01
 *  Author: 82107
 */ 

#include "essential.h"


void Receiver_init(void)
{
	#if 1
	cbi(SREG, 7);
	
	EICRB = 0xC0; //INT7 rising edge ON
	EIMSK = 0x80; //INT7 Enable

	sbi(EIFR, INTF7);

	cbi(DDRE, 7); //INT7핀 입력
	sbi(PORTE, 7); //Pull-up?

	sbi(SREG,7);
	#endif
	
	#if 0
	cbi(SREG, 7);
	
	EICRA = 0xF0; //INT2, INT3
	EICRB = 0x3C; //INT5, INT6
	EIMSK = 0x6C;
	
	sbi(EIFR, INTF2);
	sbi(EIFR, INTF3);
	sbi(EIFR, INTF5);
	sbi(EIFR, INTF6);
	
	cbi(DDRD, 2);
	cbi(DDRD, 3);
	cbi(DDRE, 5);
	cbi(DDRE, 6);
	
	sbi(PORTD, 2);
	sbi(PORTD, 3);
	sbi(PORTE, 5);
	sbi(PORTE, 6);
	
	sbi(SREG, 7);
	#endif
}
