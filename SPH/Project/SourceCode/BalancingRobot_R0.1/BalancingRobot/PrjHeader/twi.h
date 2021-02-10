/*
 * twi.h
 *
 * Created: 2020-11-07 오전 3:11:31
 *  Author: SON
 */ 


#ifndef TWI_H_ //동일한 C파일내에 동일한 H를 참조할 때 내용이 중복되는 것을 방지
#define TWI_H_

#include "PrjHeader.h"

void i2c_init(void);
unsigned char i2c_start(unsigned char address);
unsigned char i2c_rep_start(unsigned char address);
void i2c_stop(void);
unsigned char i2c_write(unsigned char data);
unsigned char i2c_readAck(void);
unsigned char i2c_readNak(void);

#endif /* TWI_H_ */