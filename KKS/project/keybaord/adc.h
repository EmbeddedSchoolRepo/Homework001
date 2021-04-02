/*
 * adc.h
 *
 * Created: 2021-01-11 오후 2:43:28
 *  Author: KKS
 */ 


#ifndef ADC_H_
#define ADC_H_

#define AREF_1_1V   0xC0
#define ADC8        0x08

void adc_init();
uint16_t adc_read();
void adc_stop();
void gen_random_add(uint8_t* add);




#endif /* ADC_H_ */