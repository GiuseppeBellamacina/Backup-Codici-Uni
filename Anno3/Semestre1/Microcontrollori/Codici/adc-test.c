/*
 * adc-test.c
 *
 *  Created on: Oct 24, 2018
 *      Author: corrado
 */


#include <stdio.h>
#include "stm32_unict_lib.h"

void main(void)
{
	DISPLAY_init();

	ADC_init(ADC1, ADC_RES_8, ADC_ALIGN_RIGHT);
	ADC_channel_config(ADC1, GPIOC, 0, 10);
	ADC_on(ADC1);
	ADC_sample_channel(ADC1, 10);

	for (;;) {
		ADC_start(ADC1);
		while (!ADC_completed(ADC1)) {}
		int value = ADC_read(ADC1);
		char s[5];
		sprintf(s, "%4d", value);
		DISPLAY_puts(0,s);
	}
}
