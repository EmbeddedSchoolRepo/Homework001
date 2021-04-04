/*
 * I2C.h
 *
 * Created: 2020-12-23 오전 3:47:57
 *  Author: 82107
 */ 


#ifndef I2C_H_
#define I2C_H_

void i2c_init(void);
uint8_t i2c_start(void);
uint8_t i2c_rep_start(void);
void i2c_stop(void);
uint8_t i2c_SLA_W(uint8_t address);
uint8_t i2c_write_data(uint8_t data);
uint8_t i2c_SLA_R(uint8_t address);
uint8_t i2c_readACK(void);
uint8_t i2c_readNACK(void);




#endif /* I2C_H_ */