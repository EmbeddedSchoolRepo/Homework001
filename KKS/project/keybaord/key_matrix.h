/*
 * key_matrix.h
 *
 * Created: 2020-11-12 오후 1:50:35
 *  Author: KKS
 */ 


#ifndef KEY_MATRIX_H_
#define KEY_MATRIX_H_

#define NUM_ROW		5
#define NUM_COL		4

#define ROW0		PORTB0
#define ROW1		PORTB1
#define ROW2		PORTC1
#define ROW3		PORTC2
#define ROW4		PORTC3 

#define COL0		PORTD4
#define COL1		PORTD5
#define COL2		PORTD6
#define COL3		PORTD7

#define COL_OFFSET  4
#define HIGH_BYTE_MASK 0Xf0
#define ALL_KEY_OPEN 0x0f

void key_io_init();
void key_int_init();
void key_timer_init();
uint8_t key_scan();
void key_send();
void All_row_to_low();
void All_row_to_high();
void view_matrix();
uint8_t getBit(uint8_t, uint8_t);
void enable_pc_int(void);
void disable_pc_int(void);

extern volatile uint8_t phase;


#endif /* KEY_MATRIX_H_ */