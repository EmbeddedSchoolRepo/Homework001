/*
 * power_clock.h
 *
 * Created: 2021-01-11 오전 11:16:55
 *  Author: KKS
 */ 


#ifndef POWER_CLOCK_H_
#define POWER_CLOCK_H_

enum power_mode
{
	idle,
	adc_noise_reduction,
	power_down,
	power_save,
	stand_by = 6,
	external_stand_by,
	normaral
};


void Clk_set(uint8_t clk_divide_val);
void Power_set(enum power_mode mode_val);
void Sleep_cpu(void);


	



#endif /* POWER_CLOCK_H_ */