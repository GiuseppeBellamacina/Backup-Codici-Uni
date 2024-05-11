/*
 * main.c
 *
 *  Created on: Feb 22, 2020
 *      Author: corrado
 */

#include "stm32_unict_lib.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

enum {
	ST_IDLE,
	ST_CLOSING,
	ST_RUNNING,
	ST_OPENING,
	ST_CONFIG
};

int state = ST_IDLE;
int current_floor = 2;
int target_floor = 2;
int reserved_floor = 0;
int tick_counter = 0, flash_counter = 0;

int lift_speed = 10;

int main()
{
	GPIO_init(GPIOC);
	GPIO_init(GPIOB);
	DISPLAY_init();
	CONSOLE_init();

	// LED at PC3
	GPIO_config_output(GPIOC, 3);

	GPIO_config_output(GPIOB, 8);

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

	// init ADC
	ADC_init(ADC1, ADC_RES_6, ADC_ALIGN_RIGHT);
	ADC_channel_config(ADC1, GPIOC, 1, 11);
	ADC_channel_config(ADC1, GPIOC, 0, 10);

	ADC_on(ADC1);
	ADC_sample_channel(ADC1, 11);

	// init the timer
	TIM_init(TIM2);

	// Configure the timebase
	// Counter clock set to 50 ms
	TIM_config_timebase(TIM2, 8400, 500);

	TIM_set(TIM2, 0); // resets the counter
	TIM_on(TIM2); // starts the timer

	TIM_enable_irq(TIM2, IRQ_UPDATE);

	// infinite loop
	for (;;) {
		char s[5];
		if (state != ST_CONFIG) {
			sprintf(s,"%3d%c",
						current_floor / 2,
						(current_floor % 2) == 1 ? '-' : ' ');
			DISPLAY_puts(0, s);
		}
		else {
			int speed_steps;
			float real_speed;
			while (state == ST_CONFIG) {
				ADC_start(ADC1);
				while (!ADC_completed(ADC1)) {}
				speed_steps = ADC_read(ADC1) * 6.0 / 63;
				real_speed = speed_steps * 0.1 + 0.4;
				sprintf(s,"%4d", (int)(real_speed * 10));
				DISPLAY_puts(0, s);
				DISPLAY_dp(2,1);
			}
			lift_speed = (real_speed / 2.0) / 0.05;
			DISPLAY_dp(2,0);
		}
	}
}

void clr_tick_counters(void)
{
	tick_counter = 0;
	flash_counter = 0;
}

void goto_floor(int floor)
{
	if (state == ST_IDLE) {
		if (floor == current_floor)
			return;
		target_floor = floor;
		clr_tick_counters();
		state = ST_CLOSING;
	}
	else if (state != ST_CONFIG) {
		reserved_floor = floor;
	}
}

void TIM2_IRQHandler(void)
{
	// check the update event
	if (TIM_update_check(TIM2)) {
		++tick_counter;
		++flash_counter;
		switch (state) {
		case ST_CLOSING:
			if (flash_counter == 4) {
				GPIO_toggle(GPIOB, 0);
				flash_counter = 0;
			}
			if (tick_counter == 60) {
				clr_tick_counters();
				GPIO_write(GPIOB, 0, 0);
				state = ST_RUNNING;
			}
			break;
		case ST_RUNNING:
			if (flash_counter == 4) {
				GPIO_toggle(GPIOC, 2);
				flash_counter = 0;
			}
			if (tick_counter >= lift_speed) {
				clr_tick_counters();
				if (current_floor == target_floor) {
					GPIO_write(GPIOC, 3, 0);
					state = ST_OPENING;
				}
				else if (current_floor > target_floor) {
					current_floor--;
				}
				else {
					current_floor++;
				}
			}
			break;
		case ST_OPENING:
			if (flash_counter == 4) {
				GPIO_toggle(GPIOC, 3);
				flash_counter = 0;
			}
			if (tick_counter == 60) {
				clr_tick_counters();
				GPIO_write(GPIOC, 3, 0);
				state = ST_IDLE;
				if (reserved_floor > 0) {
					int new_floor = reserved_floor;
					reserved_floor = 0;
					goto_floor(new_floor);
				}
			}
			break;
		}
		// clear the update event
		TIM_update_clear(TIM2);
	}
}

// tasto 'X'
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_isset(EXTI10)) {
		goto_floor(2); // floor 1
		EXTI_clear(EXTI10);
	}
}

// tasto 'Y'
void EXTI4_IRQHandler(void)
{
	if (EXTI_isset(EXTI4)) {
		goto_floor(4); // floor 2
		EXTI_clear(EXTI4);
	}
}

// tasto 'Z' & 'T'
void EXTI9_5_IRQHandler(void)
{
	if (EXTI_isset(EXTI5)) { //'Z'
		goto_floor(6); // floor 3
		EXTI_clear(EXTI5);
	}
	if (EXTI_isset(EXTI6)) { //'T'
		if (state == ST_IDLE) {
			state = ST_CONFIG;
		}
		else if (state == ST_CONFIG) {
			state = ST_IDLE;
		}
		EXTI_clear(EXTI6);
	}
}
