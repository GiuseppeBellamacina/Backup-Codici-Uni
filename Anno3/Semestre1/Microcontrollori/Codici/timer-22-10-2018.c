/*
 * timer-22-10-2018.c
 *
 *  Created on: Oct 22, 2018
 *      Author: corrado
 */

#include "stm32_unict_lib.h"
#include <stdio.h>

enum {
	ST_IDLE,
	ST_SETUP,
	ST_RUN
};

int state = ST_IDLE;

int seconds = 0, centiseconds = 0;
int setup_seconds = 0, setup_centiseconds = 0;
int flash_counter = 0;

int main(void)
{
	DISPLAY_init();
	GPIO_init(GPIOB);
	GPIO_init(GPIOC);
	GPIO_config_input(GPIOB, 10);
	GPIO_config_input(GPIOB, 4);
	GPIO_config_input(GPIOB, 5);
	GPIO_config_input(GPIOB, 6);

	GPIO_config_output(GPIOB, 0);
	GPIO_config_output(GPIOC, 3);
	GPIO_config_output(GPIOC, 2);
	GPIO_config_output(GPIOB, 8);

	GPIO_config_EXTI(GPIOB, EXTI10);
	GPIO_config_EXTI(GPIOB, EXTI4);
	GPIO_config_EXTI(GPIOB, EXTI5);
	GPIO_config_EXTI(GPIOB, EXTI6);

	EXTI_enable(EXTI10, FALLING_EDGE);
	EXTI_enable(EXTI4, FALLING_EDGE);
	EXTI_enable(EXTI5, FALLING_EDGE);
	EXTI_enable(EXTI6, FALLING_EDGE);

	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 8400, 100); // timer al centesimo di secondo
	TIM_enable_irq(TIM2, IRQ_UPDATE);
	TIM_set(TIM2, 0);
	TIM_on(TIM2);

	GPIO_write(GPIOB, 8, 1);
	for (;;) {
		char s[5];
		switch(state) {
		case ST_SETUP:
			GPIO_write(GPIOC, 2, 1);
			sprintf(s, "%02d%02d", setup_seconds, setup_centiseconds);
			break;
		default:
			GPIO_write(GPIOC, 2, 0);
			sprintf(s, "%02d%02d", seconds, centiseconds);
			break;
		}
		DISPLAY_puts(0, s);
	}
}

// tasto 'X'
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_isset(EXTI10)) {
		switch (state) {
		case ST_IDLE:
			state = ST_SETUP;
			break;
		case ST_SETUP:
			seconds = setup_seconds;
			centiseconds = setup_centiseconds;
			state = ST_IDLE;
			break;
		}
		EXTI_clear(EXTI10);
	}
}

// tasto 'Y'
void EXTI4_IRQHandler(void)
{
	if (EXTI_isset(EXTI4)) {
		switch (state) {
		case ST_IDLE:
			state = ST_RUN;
			break;
		case ST_RUN:
			state = ST_IDLE;
			break;
		}
		EXTI_clear(EXTI4);
	}
}

// tasto 'Z' & 'T'
void EXTI9_5_IRQHandler(void)
{
	if (EXTI_isset(EXTI5)) { //'Z'
		switch(state) {
		case ST_IDLE:
		case ST_RUN:
			seconds = setup_seconds;
			centiseconds = setup_centiseconds;
			break;
		case ST_SETUP:
			if (setup_seconds > 0)
				--setup_seconds;
			break;
		}
		EXTI_clear(EXTI5);
	}
	if (EXTI_isset(EXTI6)) { //'T'
		switch(state) {
		case ST_SETUP:
			if (setup_seconds < 99)
				++setup_seconds;
			break;
		}
		EXTI_clear(EXTI6);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_update_check(TIM2)) {
		switch (state) {
		case ST_RUN:
			if ((seconds == 0) && (centiseconds == 0)) {
				GPIO_write(GPIOC, 3, 1);
			}
			else {
				GPIO_write(GPIOC, 3, 0);
				flash_counter++;
				if (flash_counter >= 50) {
					GPIO_toggle(GPIOB, 0);
					flash_counter = 0;
				}
				if (centiseconds > 0)
					--centiseconds;
				if (centiseconds == 0) {
					if (seconds > 0) {
						--seconds;
						centiseconds = 99;
					}
				}
			}
			break;
		default:
			GPIO_write(GPIOC, 3, 0);
			break;
		}
		TIM_update_clear(TIM2);
	}
}

