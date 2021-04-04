/*
 * Receiver.h
 *
 * Created: 2021-01-17 오전 4:05:41
 *  Author: 82107
 */ 


#ifndef RECEIVER_H_
#define RECEIVER_H_

#define COUNT_s 0.0000005 // 1카운트 당 0.0000005s


/* 최소:600us, 중간:1100us, 최대:1600us */

typedef struct Receiver_
{
	uint16_t ch1;
	uint16_t ch2;
	uint16_t ch3;
	uint16_t ch4;
	uint16_t ch5;
	uint16_t ch6;
	uint16_t ch7;
	uint16_t ch8;
	
	uint16_t remainder_value;

}Receiver;

void Receiver_init(void);



#endif /* RECEIVER_H_ */