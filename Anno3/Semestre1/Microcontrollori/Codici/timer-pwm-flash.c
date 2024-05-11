/*
 * timer-pwm-flash.c
 *
 *  Created on: Nov 5, 2018
 *      Author: corrado
 */

#include "stm32_unict_lib.h"

void main(void)
{
	GPIO_init(GPIOB);
	GPIO_config_alternate(GPIOB, 0, 2); // AF2 --> TIMER3, CH3

	TIM_init(TIM3);
	// f = 84MHz
	// PSC = 60000
	// frequenza di incremento = 84Mhz/60000 = 1400Hz
	// durata di un tick di incremento ~= 0.7ms
	// P = 600ms --> ~ 858 count
	TIM_config_timebase(TIM3, 60000, 858);
	TIM_config_PWM(TIM3, 3); // TIMER3, CH3
	// Ton = 50ms -> ~ 72 count
	TIM3->CCR3 = 72;
	TIM_set(TIM3, 0);
	TIM_on(TIM3);

	for (;;) { }
}
