/*
 * SPI.h
 *
 * Created: 2021-02-19 오후 1:49:34
 *  Author: 82107
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_init(void);
uint8_t SPI_read(uint8_t reg_address);
void SPI_write(uint8_t reg_address, uint8_t data);
void mpu6050_init_SPI(void);
void get_accel_gyro_raw_SPI(accel_t_gyro* Paccel_gyro);
void get_accel_gyro_ave_SPI(accel_t_gyro* Paccel_gyro);
void mpu6050_run_SPI(accel_t_gyro* Paccel_gyro, accel_t_gyro* Paccel_gyro_ave, angle* Fil_angle);



#endif /* SPI_H_ */