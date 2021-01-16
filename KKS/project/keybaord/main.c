/*
 * nrf24l01.c
 *
 * Created: 2020-12-22 오전 9:40:34
 * Author : KKS
 */ 

#define F_CPU 16000000UL

#define sbi(RegX,bit) RegX |= (1<<bit)
#define cbi(RegX,bit) RegX &= ~(1<<bit)

#include <avr/io.h>

#include "spi.h"
#include "uart.h"
#include "adc.h"
#include "TWI.h"
#include "nrf24l01.h"
#include "power_clock.h"
#include "key_matrix.h"
#include "mtch6102.h"


static uint16_t  send_count = 0;

void loop(void);

#define DO_NOTHING      0
#define PIN_CHANGE_INT	     1   
#define TIMER_INT   2
#define TOUCH_INT   3

volatile uint8_t phase = DO_NOTHING;

int main(void)
{
    /* Replace with your application code */
	_delay_ms(100);
	
	FILE* fpStdio = fdevopen(usartTxChar,NULL);
	
	uart_init();
	SPI_Master_Init();
	nrf24_port_init();
	key_int_init();
	key_io_init();
	key_timer_init();
	i2c_init();
	//mtch6102_dump_register();
	nrf24_init();
	nrf24_dump_registers();
	adc_init();
	gen_random_add(tranceiver_addr);
	adc_stop();
	
	for(uint8_t i=0;i<ADDR_WIDTH;i++)
	{
		printf("tranceiver_addr : %02x \n",tranceiver_addr[i]);
	}

	All_row_to_low();
	phase = DO_NOTHING;
	enable_pc_int();
	Power_set(power_down);

    while (1) 
	{
		switch(phase)
		{
			case DO_NOTHING: //Before 1:1 link, wait 1:1 link with dongle 
				break;
				
			 /********************************************************************
			                      AFTER PIN CHANGE INTERRUPT PHASE
			  ********************************************************************/ 	
			case PIN_CHANGE_INT: //Do 1:1 link,
				disable_pc_int();
				printf("Pin_Chnage_interrupt_occur!\n");
				sbi(TIMSK2,OCIE2A); //Timer Counter interrupt enable #DEFINE 함수로 바꾸기
				Power_set(idle);
				phase = DO_NOTHING;
				break;
				
			 /********************************************************************
			                      AFTER TIMER INTERRUPT PHASE
			  ********************************************************************/ 
			case TIMER_INT:  //normaral phase, then scan key matrix
				printf("Timer_Over_Flow_occur!\n");
				cbi(TIMSK2,OCIE2A); //disable TIMER interrupt #DEFINE 함수로 바꾸기
				while(1)
				{
					uint8_t key_status;
					key_status = key_scan();
					if(key_status == ALL_KEY_OPEN)
					{
						break;
					}
					printf("do_scanning\r");
				}
			
				view_matrix();
				phase = DO_NOTHING;
				All_row_to_high();
				printf("high!\n");
				enable_pc_int();
				printf("low!\n");
				printf("phase : %d \n",phase);
				All_row_to_low();
				Power_set(power_down);
				//send_data;
				break;
				
			 /********************************************************************
			                      AFTER TOUCH INTERRUPT PHASE
			  ********************************************************************/ 
			case TOUCH_INT : 
				break;	
				
			default:
				break;
		}
	}
}

void loop(void)
{
	nrf24_send((void*)&send_count, 2);

	send_count++;
	_delay_ms(200);
}

