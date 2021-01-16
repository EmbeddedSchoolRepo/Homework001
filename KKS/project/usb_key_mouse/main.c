
/**************************************************************
작성자 : KKS
참고   : TEENSY 2.0 KEYBOARD PROJECT

MCU :   ATmega32u4
BOARD : ARDUINO LEONARDO 
H/W   : 5V 
CLOCK : 16Mhz
 
주요 기능
1. USB 통신
2. HID2.0 KEYBOARD
3. HID2.0 MOUSE
4. NRF24L01 무선 데이터 송수신    
**************************************************************/
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usb.h"
#include "spi.h"
#include "uart.h"
#include "nrf24l01.h"

/*
uint8_t number_keys[10]=
{KEY_0,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9};
*/


int main(void)
{
    /* Replace with your application code */
	uint8_t* main_status;

	_delay_ms(100);
	FILE* fpStdio = fdevopen(usartTxChar,NULL);
	uart_init();
	SPI_Master_Init();
	printf("ATmega32u4_UART_INIT_COMPLETE\n");
	printf("ATmega32u4_SPI_INIT_COMPLETE\n");
	nrf24_pin_init();
	nrf24_init();
	nrf24_dump_registers();
	ce_high();
		
	usb_init();
	while (!usb_configured()) /* wait */ ;
	_delay_ms(1000);
	
    while(1) 
    {

				
			
			 
			
    }
}


static uint8_t rx_buf[PAYLOAD_WIDTH];

void loop(void)
{
	if (nrf24_receive(rx_buf, PAYLOAD_WIDTH) > 0)
	{
		uint16_t     *data = (uint16_t *)rx_buf;
		printf("\x1B[25DData = %5d", *data);
	}
}

ISR(INT0_vect) //WHEN IRQ LOW 
{
	printf("IRQ_OCCUR!\n");
}

