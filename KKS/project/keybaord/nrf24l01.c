/*
 * nrf24l01.c
 *
 * Created: 2020-12-22 오전 10:43:25
 *  Author: KKS
 */ 
#define F_CPU 16000000UL

#include <stdio.h>
#include "uart.h"
#include "spi.h"
#include "nrf24l01.h"
#include <util/delay.h>


#define SCK     0x20
#define MISO    0x10
#define MOSI    0x08
#define CS      0x04
#define CE      0x02

void cs_high(void)
{
	PORTB |= CS;
}

void cs_low(void)
{
	PORTB &= ~CS;
}

void ce_high(void)
{
	PORTB |= CE;
}

void ce_low(void)
{
	PORTB &= ~CE;
}

void nrf24_port_init(void)
{
	DDRB |= (SCK | MOSI | CS | CE);
	PORTB |= (MISO | CS);
}


static uint8_t nrf24_read_reg(uint8_t reg, uint8_t *data, int len)
{
	uint8_t val = 0;
	int     i;

	cs_low();

	SPI_TxRx(reg);
	if (data && len)
	{
		for (i=0; i<len; i++)
		{
			*data++ = SPI_TxRx(NOP);
		}
	}

	val = SPI_TxRx(NOP);

	cs_high();

	return val;
}

static uint8_t nrf24_write_reg(uint8_t reg, uint8_t *data, int len)
{
	uint8_t val = 0;
	int     i;

	cs_low();

	if (reg < WR_REG)
	reg += WR_REG;

	val = SPI_TxRx(reg);

	if (data && len)
	{
		for (i=0; i<len; i++)
		{
			SPI_TxRx(*data++);
		}
	}

	cs_high();

	return val;
}

static void nrf24_write_payload(uint8_t *data, int len)
{
	uint8_t dummy = PAYLOAD_WIDTH - len;

	cs_low();
	SPI_TxRx(WR_TX_PAYLOAD);
	while (len--)
	SPI_TxRx(*data++);
	while (dummy--)
	SPI_TxRx(0);
	cs_high();
}

static void nrf24_close_pipe(enum nrf_pipe pipe)
{
	uint8_t     aa = 0;
	uint8_t     rxaddr = 0;

	if (pipe != NRF_ALL)
	{
		aa = nrf24_read_reg(EN_AA_REG, NULL, 0) & ~(1<<pipe);
		rxaddr = nrf24_read_reg(EN_RXADDR_REG, NULL, 0) & ~(1<<pipe);
	}

	nrf24_write_reg(EN_AA_REG, &aa, 1);
	nrf24_write_reg(EN_RXADDR_REG, &rxaddr, 1);
}

static void nrf24_open_pipe(enum nrf_pipe pipe)
{
	uint8_t     aa = 0x3F;
	uint8_t     rxaddr = 0x3F;

	if (pipe != NRF_ALL)
	{
		aa = nrf24_read_reg(EN_AA_REG, NULL, 0) | (1<<pipe);
		rxaddr = nrf24_read_reg(EN_RXADDR_REG, NULL, 0) | (1<<pipe);
	}

	nrf24_write_reg(EN_AA_REG, &aa, 1);
	nrf24_write_reg(EN_RXADDR_REG, &rxaddr, 1);
}

static void nrf24_crc_mode(enum crc_mode crc)
{	
	uint8_t     config = 0;
	
	config = (nrf24_read_reg(CONFIG_REG, NULL, 0) & ~0x0C) | (crc << 2);
	nrf24_write_reg(CONFIG_REG, &config, 1);
}

static void nrf24_auto_retr(uint8_t arc, uint16_t ard)
{
	uint8_t     data = (((ard/250)-1) << 4) | arc;

	nrf24_write_reg(SETUP_RETR_REG, &data, 1);
}

static void nrf24_addr_width(enum address_width aw)
{
	nrf24_write_reg(SETUP_AW_REG, (uint8_t*)&aw, 1);
}

static void nrf24_set_addr(enum nrf_pipe pipe, uint8_t *addr)
{
	uint8_t     aw = nrf24_read_reg(SETUP_AW_REG, NULL, 0) + 2; //BYTE수와 매칭하기 위한 OFFSET +2 

	switch (pipe)
	{
		case NRF_PIPE0:
		case NRF_PIPE1:
		case NRF_TX:
		nrf24_write_reg(RX_ADDR_P0_REG + pipe, addr, aw);
		break;

		case NRF_PIPE2 ... NRF_PIPE5:
		nrf24_write_reg(RX_ADDR_P0_REG + pipe, addr, 1);
		break;

		default:
		break;
	}

}

static void nrf24_op_mode(enum op_mode mode)
{
	uint8_t     config = nrf24_read_reg(CONFIG_REG, NULL, 0);

	if (mode == NRF_PTX)
	{
		config &= ~PRIM_RX;
	}
	else
	{
		config |= PRIM_RX;
	}

	nrf24_write_reg(CONFIG_REG, &config, 1);
}

static void nrf24_rf_channel(uint8_t rf_ch)
{
	nrf24_write_reg(RF_CH_REG, (uint8_t*)&rf_ch, 1);
}

static void nrf24_rf_data_rate(enum data_rate bps)
{
	uint8_t     rf = nrf24_read_reg(RF_SETUP_REG, NULL, 0);

	if (bps == NRF_1MBPS)
	{
		rf &= ~(1<<3);
	}
	else
	{
		rf |= (1<<3);
	}

	nrf24_write_reg(RF_SETUP_REG, &rf, 1);
}

static void nrf24_power_mode(enum pwr_mode mode)
{
	uint8_t     config = nrf24_read_reg(CONFIG_REG, NULL, 0);

	if (mode == NRF_PWR_DOWN)
	{
		config &= ~POWER_UP;
	}
	else
	{
		config |= POWER_UP;
	}

	nrf24_write_reg(CONFIG_REG, &config, 1);
}

static void nrf24_flush_tx(void)
{
	nrf24_write_reg(FLUSH_TX, NULL, 0);

}

static void nrf24_flush_rx(void)
{
	nrf24_write_reg(FLUSH_RX, NULL, 0);
}

/*============================================================================*/

void nrf24_dump_registers(void)
{
    uint8_t     addr[ADDR_WIDTH];
    int         i;

    printf("\n\nnRF24L01 Registers Value\n");

    printf("    CONFIG : %02X\n", nrf24_read_reg(CONFIG_REG, NULL, 0));
    printf("     EN_AA : %02X\n", nrf24_read_reg(EN_AA_REG, NULL, 0));
    printf(" EN_RXADDR : %02X\n", nrf24_read_reg(EN_RXADDR_REG, NULL, 0));
    printf("  SETUP_AW : %02X\n", nrf24_read_reg(SETUP_AW_REG, NULL, 0));
    printf("SETUP_RETR : %02X\n", nrf24_read_reg(SETUP_RETR_REG, NULL, 0));
    printf("     RF_CH : %02X\n", nrf24_read_reg(RF_CH_REG, NULL, 0));
    printf("  RF_SETUP : %02X\n", nrf24_read_reg(RF_SETUP_REG, NULL, 0));
    printf("    STATUS : %02X\n", nrf24_read_reg(STATUS_REG, NULL, 0));

    nrf24_read_reg(RX_ADDR_P0_REG, addr, ADDR_WIDTH);
    printf("RX_ADDR_P0 : ");
    for (i=0; i<ADDR_WIDTH; i++)
    printf("%02X", addr[i]);
    printf("\n");

    nrf24_read_reg(RX_ADDR_P1_REG, addr, ADDR_WIDTH);
    printf("RX_ADDR_P1 : ");
    for (i=0; i<ADDR_WIDTH; i++)
    printf("%02X", addr[i]);
    printf("\n");

    printf("RX_ADDR_P2 : %02X\n", nrf24_read_reg(RX_ADDR_P2_REG, NULL, 0));
    printf("RX_ADDR_P3 : %02X\n", nrf24_read_reg(RX_ADDR_P3_REG, NULL, 0));
    printf("RX_ADDR_P4 : %02X\n", nrf24_read_reg(RX_ADDR_P4_REG, NULL, 0));
    printf("RX_ADDR_P5 : %02X\n", nrf24_read_reg(RX_ADDR_P5_REG, NULL, 0));

    nrf24_read_reg(TX_ADDR_REG, addr, ADDR_WIDTH);
    printf("   TX_ADDR : ");
    for (i=0; i<ADDR_WIDTH; i++)
    printf("%02X", addr[i]);
    printf("\n");

    printf(" RX_PWD_P0 : %02X\n", nrf24_read_reg(RX_PWD_P0_REG, NULL, 0));
    printf(" RX_PWD_P1 : %02X\n", nrf24_read_reg(RX_PWD_P1_REG, NULL, 0));
    printf(" RX_PWD_P2 : %02X\n", nrf24_read_reg(RX_PWD_P2_REG, NULL, 0));
    printf(" RX_PWD_P3 : %02X\n", nrf24_read_reg(RX_PWD_P3_REG, NULL, 0));
    printf(" RX_PWD_P4 : %02X\n", nrf24_read_reg(RX_PWD_P4_REG, NULL, 0));
    printf(" RX_PWD_P5 : %02X\n", nrf24_read_reg(RX_PWD_P5_REG, NULL, 0));

    printf("FIFO_STATUS: %02X\n", nrf24_read_reg(FIFO_STATUS_REG, NULL, 0));
    printf("     DYNPD : %02X\n", nrf24_read_reg(DYNPD_REG, NULL, 0));
    printf("   FEATURE : %02X\n", nrf24_read_reg(FEATURE_REG, NULL, 0));
}

uint8_t  tranceiver_addr[ADDR_WIDTH] = {0x12, 0x34, 0x56, 0x78, 0x90};	
	
void nrf24_init(void)
{
	ce_low();
	cs_high();
	_delay_ms(10);
	printf("ok\n");
	nrf24_close_pipe(NRF_ALL);
	nrf24_open_pipe(NRF_PIPE0);
	nrf24_crc_mode(NRF_CRC_16BIT);
	nrf24_auto_retr(15, 500);

	nrf24_addr_width(NRF_AW_5BYTES);
	nrf24_set_addr(NRF_TX, tranceiver_addr);
	nrf24_set_addr(NRF_PIPE0, tranceiver_addr);

	nrf24_op_mode(NRF_PTX);
	nrf24_rf_channel(76);
	nrf24_rf_data_rate(NRF_1MBPS);

	nrf24_flush_tx();
	nrf24_flush_rx();

	nrf24_power_mode(NRF_PWR_UP);

	_delay_ms(10);
}

void nrf24_send(uint8_t *buf, uint8_t len)
{
	uint8_t status, clear;

	nrf24_write_payload(buf, len);

	ce_high();
	_delay_us(20);
	ce_low();
	
	printf("BUF: %d\n",*buf);
	
	do
	{
		status = nrf24_read_reg(STATUS_REG, NULL, 0);
		printf("status : %d\n",status);
	} while(!(status & (TX_DS | MAX_RT)));

	if (status & TX_DS)
	{
		clear = TX_DS;
		nrf24_write_reg(STATUS_REG, &clear, 1);
		printf("normarl\n");
	}
	if (status & MAX_RT)
	{
		clear = MAX_RT;
		nrf24_write_reg(STATUS_REG, &clear, 1);
		nrf24_flush_tx();
		printf("Maximum number of Tx\n");
	}
}
