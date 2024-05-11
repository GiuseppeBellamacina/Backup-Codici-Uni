/*
 * reaction-game.c
 *
 *  Created on: Nov 5, 2018
 *      Author: corrado
 */


#include "stm32_unict_lib.h"
#include <stdio.h>
#include <stdlib.h>

int measure_done, timeout, started;

int main()
{
	DISPLAY_init();
	GPIO_init(GPIOB);
	GPIO_init(GPIOC);
	GPIO_config_output(GPIOB, 0); // 'red' LED
	GPIO_config_output(GPIOC, 2); // 'yellow' LED
	GPIO_config_input(GPIOB, 10); // tasto 'X'
	GPIO_config_EXTI(GPIOB, EXTI10);
	EXTI_enable(EXTI10, FALLING_EDGE);

	GPIO_config_alternate(GPIOB, 4, 2); // button "Y" as AF2 --> TIM3,CH1
	TIM_init(TIM3);
	TIM_config_timebase(TIM3, 8400, 50000); // prescaler at 100us timeout of 5 secs
	TIM_config_IC(TIM3, 1, IC_FALLING_EDGE); // capture on falling-edge (pushbutton)
	TIM_set(TIM3, 0);
	TIM_on(TIM3);
	TIM_enable_irq(TIM3, IRQ_UPDATE | IRQ_CC_1); // IRQ su UPDATE e su Capture canale 1

	for (;;) {
		started = 0;
		while (!started) { } // wait 'X'
		GPIO_write(GPIOB, 0, 1); // turn on LED

		int t = 1000 + (rand() * 3000) / RAND_MAX; // random from 1000 to 4000 ms
		delay_ms(t); // wait t milliseconds to start the game
		TIM_set(TIM3, 0); // clear timer and flags
		measure_done = 0;
		timeout = 0;
		GPIO_write(GPIOC, 2, 1); // turn on LED
		DISPLAY_puts(0, "    ");

		while (!measure_done && !timeout) { } // wait for capture or timeout
		if (measure_done) {
			// capture OK!
			int ms = TIM3->CCR1 / 10;
			char s[5];
			sprintf(s,"%4d", ms);
			DISPLAY_puts(0, s);
		}
		else {
			// timeout
			DISPLAY_puts(0, "tout");
		}
	}
}

void TIM3_IRQHandler(void)
{
	if (TIM_update_check(TIM3)) {
		// period match, timeout
		GPIO_write(GPIOB, 0, 0);
		GPIO_write(GPIOC, 2, 0);
		timeout = 1;
		TIM_update_clear(TIM3);
	}
	if (TIM_cc_check(TIM3,1)) {
		// capture
		GPIO_write(GPIOB, 0, 0);
		GPIO_write(GPIOC, 2, 0);
		measure_done = 1;
		TIM_cc_clear(TIM3,1);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_isset(EXTI10)) {
		started = 1;
		EXTI_clear(EXTI10);
	}
}
