/*
 * ultrasonic-sensor.c
 *
 *  Created on: Nov 5, 2018
 *      Author: corrado
 */


#include "stm32_unict_lib.h"
#include <stdio.h>
#include <stdlib.h>

int measure_done, sample;
uint16_t start_time, us;

int main()
{
	DISPLAY_init();
	GPIO_init(GPIOA);

	GPIO_config_output(GPIOA, 1);
	GPIO_config_alternate(GPIOA, 0, 1); // AF1 --> TIM2,CH1

	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 84, 50000); // prescaler at 1us timeout of 50 msecs
	TIM_config_IC(TIM2, 1, IC_BOTH_EDGES); // capture on both edges
	TIM_set(TIM2, 0);
	TIM_on(TIM2);
	TIM_enable_irq(TIM2, IRQ_UPDATE | IRQ_CC_1); // IRQ su UPDATE e su Capture canale 1

	GPIO_write(GPIOA, 1, 0);
	//DISPLAY_puts(0, "st  ");
	sample = 0;
	measure_done = 0;

	for (;;) {
		while (!sample) {}
		sample = 0;
		measure_done = 0;
		TIM_set(TIM2,0);
		GPIO_write(GPIOA, 1, 1);
		delay_ms(1);
		GPIO_write(GPIOA, 1, 0);

		while (!measure_done && !sample) { } // wait for capture or sample timeout

		if (measure_done) {
			// capture OK!
			char s[5];
			float distance = us / 58.0;
			sprintf(s,"%4d", (int)distance);
			DISPLAY_puts(0, s);
		}
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_update_check(TIM2)) {
		// period match, sample timeout
		sample = 1;
		TIM_update_clear(TIM2);
	}
	if (TIM_cc_check(TIM2,1)) {
		// capture
		if (GPIO_read(GPIOA, 0) == 1) { // fronte di salita
			start_time = TIM2->CCR1;
		}
		else { // fronte di discesa
			us = TIM2->CCR1 - start_time;
			measure_done = 1;
		}
		TIM_cc_clear(TIM2,1);
	}
}
