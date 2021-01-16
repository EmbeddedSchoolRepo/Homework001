/*
 * spi.h
 *
 * Created: 2020-12-28 오후 1:01:21
 *  Author: KKS
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_Master_Init(void);
void SPI_Slave_Init(void);
unsigned char SPI_TxRx(unsigned char Data);

#endif /* SPI_H_ */