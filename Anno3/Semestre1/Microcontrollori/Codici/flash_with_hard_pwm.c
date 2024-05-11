/*
 * adc_test.c
 *
 *  Created on: Dec 3, 2017
 *      Author: corrado
 */

#include <stdio.h>
#include "stm32_unict_lib.h"

#define PERIOD_PWM   1000

int led_on = 0;
int t_on;
int p_flash = 200;

int main(void)
{
	DISPLAY_init();

	GPIO_init(GPIOB);
	GPIO_config_alternate(GPIOB, 8, 2); // AF2 -> TIM4 CH3

	ADC_init(ADC1, ADC_RES_8, ADC_ALIGN_RIGHT);
	ADC_channel_config(ADC1, GPIOC, 0, 10);
	ADC_channel_config(ADC1, GPIOC, 1, 11);
	ADC_on(ADC1);

	TIM_init(TIM4);
	TIM_config_timebase(TIM4, 420, PERIOD_PWM);
	TIM_set(TIM4, 0);
	TIM_config_PWM(TIM4, 3);
	TIM_on(TIM4);

	TIM_init(TIM3);
	TIM_config_timebase(TIM3, 42000, 1000);
	TIM_set(TIM3, 0);
	TIM_on(TIM3);
	TIM_enable_irq(TIM3, IRQ_UPDATE);

	for (;;) {
		ADC_sample_channel(ADC1, 10);
		ADC_start(ADC1);
		while (!ADC_completed(ADC1)) {}
		int value = ADC_read(ADC1);
		t_on = (value * 1000)/255;

		ADC_sample_channel(ADC1, 11);
		ADC_start(ADC1);
		while (!ADC_completed(ADC1)) {}
		value = ADC_read(ADC1);
		p_flash = 200 + (value * 1800.0)/255;
	}
	return 0;
}

void TIM3_IRQHandler(void)
{
	if (TIM_update_check(TIM3)) {
		led_on = !led_on;
		if (led_on)
			TIM4->CCR3 = t_on;
		else
			TIM4->CCR3 = 0;
		TIM3->ARR = p_flash;
		TIM_update_clear(TIM3);
	}
}
