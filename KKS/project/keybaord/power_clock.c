/*
 * power_clock.c
 *
 * Created: 2021-01-11 오전 11:16:30
 *  Author: KKS
 */ 

#include <avr/io.h>
#include <avr/sleep.h>

#include "power_clock.h"
#include "uart.h"

#define sbi(PORTX,BitX) (PORTX |= (1<<BitX))
#define cbi(PORTX,BitX) (PORTX &= ~(1<<BitX))

void Clk_set(uint8_t clk_divide_val)
{
	CLKPR = 0x80; //low byte 레지스터에 0000을 동시에 써야 8bit에 값 쓰임.
	sbi(CLKPR,clk_divide_val>>1);
} 

void Power_set(enum power_mode mode_val) //avr core는 wakeup후 ISR수행이후 4CYCLE이 지난 다음 다시 SLEEP함.
{
	printf("Enter sleep Mode\n");
	SMCR |= (mode_val<<1);
	//SMCR |= (uint8_t)mode_val<<1; //SLEEP MODE SETTING
	sbi(SMCR,SE); //SLEEP ENABLE
	Sleep_cpu();
	cbi(SMCR,SE); //SLEEP DISABLE
}

void Sleep_cpu(void)
{
	__asm__ __volatile__ ( "sleep" "\n\t" :: );
}