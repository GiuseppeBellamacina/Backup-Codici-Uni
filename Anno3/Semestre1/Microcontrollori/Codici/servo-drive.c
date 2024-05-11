/*
 * servo-drive.c
 *
 *  Created on: Nov 7, 2018
 *      Author: corrado
 */

#include "stm32_unict_lib.h"
#include <stdio.h>

int main(void)
{
	DISPLAY_init();
	GPIO_init(GPIOA);
	GPIO_config_alternate(GPIOA, 1, 1); // AF1 = TIM2_CH2

	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 84, 20000);
	// timer tick = 1 us
	// ARR = 20000 us --> 20 ms
	TIM_config_PWM(TIM2, 2); // channel 2
	TIM2->CCR2 = 0; // 0 us di "Ton" su channel 2
	TIM_set(TIM2,0);
	TIM_on(TIM2);

	ADC_init(ADC1, ADC_RES_12, ADC_ALIGN_RIGHT);
	ADC_channel_config(ADC1, GPIOC, 0, 10);
	ADC_on(ADC1);
	ADC_sample_channel(ADC1, 10);

	for (;;) {
		ADC_start(ADC1);
		ADC_start(ADC1);
		while (!ADC_completed(ADC1)) {}
		int value = ADC_read(ADC1);
		value = (value * 1200)/4095 + 900;
		TIM2->CCR2 = value;
		char s[5];
		sprintf(s,"%4d", value);
		DISPLAY_puts(0, s);
	}
}
