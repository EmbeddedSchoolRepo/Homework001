/*
 * nrf24l01.h
 *
 * Created: 2020-12-22 오전 10:36:54
 *  Author: KKS
 */ 


#ifndef NRF24L01_H_
#define NRF24L01_H_

void nrf24_pin_init(void);
void nrf24_init(void);
void nrf24_send(uint8_t *buf, uint8_t len);
void nrf24_flush_tx_fifo(void);
void nrf24_flush_rx_fifo(void);
void nrf24_dump_registers(void);
void nrf24_port_init(void);
int nrf24_receive(uint8_t *buf, uint8_t len);


void cs_high(void);
void cs_low(void);
void ce_high(void);
void ce_low(void);

/* nRF24L01 Command */
#define RD_REG          0x00
#define WR_REG          0x20
#define RX_PAYLOAD_WD   0x60
#define RD_RX_PAYLOAD   0x61
#define WR_TX_PAYLOAD   0xA0
#define FLUSH_TX        0xE1
#define FLUSH_RX        0xE2
#define REUSE_TX_PL     0xE3
#define RD_RX_PL_WID    0x60
#define WR_ACK_PAYLOAD  0xA8
#define WR_TX_PL_NO_ACK 0xB0
#define NOP             0xFF

/* nRF24L01 Register Address */
#define CONFIG_REG      0x00
#define EN_AA_REG       0x01
#define EN_RXADDR_REG   0x02
#define SETUP_AW_REG    0x03
#define SETUP_RETR_REG  0x04
#define RF_CH_REG       0x05
#define RF_SETUP_REG    0x06
#define STATUS_REG      0x07
#define OBSERVE_TX_REG  0x08
#define RPD_REG         0x09
#define RX_ADDR_P0_REG  0x0A
#define RX_ADDR_P1_REG  0x0B
#define RX_ADDR_P2_REG  0x0C
#define RX_ADDR_P3_REG  0x0D
#define RX_ADDR_P4_REG  0x0E
#define RX_ADDR_P5_REG  0x0F
#define TX_ADDR_REG     0x10
#define RX_PWD_P0_REG   0x11
#define RX_PWD_P1_REG   0x12
#define RX_PWD_P2_REG   0x13
#define RX_PWD_P3_REG   0x14
#define RX_PWD_P4_REG   0x15
#define RX_PWD_P5_REG   0x16
#define FIFO_STATUS_REG 0x17
#define DYNPD_REG       0x1C
#define FEATURE_REG     0x1D

#define ADDR_WIDTH      5
#define PAYLOAD_WIDTH   32


/* nRF24L01 Config Register bit value */
#define MASK_RX_DR      0x40
#define MASK_TX_DS      0x20
#define MASK_MAX_RT     0x10
#define EN_CRC          0x08
#define CRC_2BYTES      0x04
#define POWER_UP        0x02
#define PRIM_RX         0x01

/* nRF24L01 Status Register bit value */
#define RX_DR           0x40
#define TX_DS           0x20
#define MAX_RT          0x10
#define TX_FULL         0x01

enum nrf_pipe
{
	NRF_PIPE0,              /**< Select pipe0 */
	NRF_PIPE1,              /**< Select pipe1 */
	NRF_PIPE2,              /**< Select pipe2 */
	NRF_PIPE3,              /**< Select pipe3 */
	NRF_PIPE4,              /**< Select pipe4 */
	NRF_PIPE5,              /**< Select pipe5 */
	NRF_TX,                 /**< Refer to TX address*/
	NRF_ALL = 0xFF          /**< Close or open all pipes*/
};

enum crc_mode
{
	NRF_CRC_OFF,        /**< CRC check disabled */
	NRF_CRC_8BIT = 2,   /**< CRC check set to 8-bit */
	NRF_CRC_16BIT       /**< CRC check set to 16-bit */
};

enum address_width
{
	NRF_AW_3BYTES = 1,      /**< Set address width to 3 bytes */
	NRF_AW_4BYTES,          /**< Set address width to 4 bytes */
	NRF_AW_5BYTES           /**< Set address width to 5 bytes */
};

enum op_mode
{
	NRF_PTX,            /**< Primary TX operation */
	NRF_PRX             /**< Primary RX operation */
};

enum pwr_mode
{
	NRF_PWR_DOWN,       /**< Device power-down */
	NRF_PWR_UP          /**< Device power-up */
};

enum data_rate
{
	NRF_1MBPS,          /**< Datarate set to 1 Mbps  */
	NRF_2MBPS           /**< Datarate set to 2 Mbps  */
};

enum output_pwr
{
	NRF_18DBM,          /**< Output power set to -18dBm */
	NRF_12DBM,          /**< Output power set to -12dBm */
	NRF_6DBM,           /**< Output power set to -6dBm  */
	NRF_0DBM            /**< Output power set to 0dBm   */
};

#endif /* NRF24L01_H_ */