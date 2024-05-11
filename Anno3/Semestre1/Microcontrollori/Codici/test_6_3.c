/*
 * test_6_3.c
 *
 *  Created on: Jan 27, 2019
 *      Author: corrado
 */

#include "stm32_unict_lib.h"
#include <stdio.h>

typedef struct {
	int mm, ss;
	int configured; // boolean flag
} t_time;

t_time current_time, on_time, off_time, adc_time;

enum {
	ST_RUN,
	ST_MENU,
	ST_SHOW,
	ST_CONFIG
};

int current_state = ST_RUN;
int current_menu = 0;

void init_peripherals(void)
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

	ADC_init(ADC1, ADC_RES_8, ADC_ALIGN_RIGHT);
	ADC_channel_config(ADC1, GPIOC, 0, 10);
	ADC_channel_config(ADC1, GPIOC, 1, 11);
	ADC_on(ADC1);

	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 8400, 10000); // timer al secondo
	TIM_enable_irq(TIM2, IRQ_UPDATE);
	TIM_set(TIM2, 0);
}

void show_time(t_time * t)
{
	char s[5];
	sprintf(s, "%02d%02d", t->mm, t->ss);
	DISPLAY_puts(0, s);
}

void show_menu(void)
{
	switch (current_menu) {
	case 0: DISPLAY_puts(0, "ti  "); break;
	case 1: DISPLAY_puts(0, "St  "); break;
	case 2: DISPLAY_puts(0, "En  "); break;
	}
}

void show_config(void)
{
	char s[5];
	switch (current_menu) {
	case 0: show_time(&current_time); break;
	case 1: show_time(&on_time); break;
	case 2: show_time(&off_time); break;
	}
	DISPLAY_puts(0, s);
}

void read_config(void)
{
	ADC_sample_channel(ADC1, 10);
	ADC_start(ADC1);
	while (!ADC_completed(ADC1)) {}
	adc_time.mm = (ADC_read(ADC1) * 59)/255;

	ADC_sample_channel(ADC1, 11);
	ADC_start(ADC1);
	while (!ADC_completed(ADC1)) {}
	adc_time.ss = (ADC_read(ADC1) * 59)/255;

	adc_time.configured = 1;

	show_time(&adc_time);
}

int main(void)
{
	init_peripherals();

	current_time.mm = 0;
	current_time.ss = 0;

	on_time.configured = 0;
	off_time.configured = 0;

	TIM_on(TIM2);

	for(;;) {
		switch (current_state) {
		case ST_RUN:
			GPIO_write(GPIOB, 0, 0);
			// show timer on display
			show_time(&current_time);
			break;
		case ST_MENU:
			GPIO_write(GPIOB, 0, 1);
			show_menu();
			break;
		case ST_SHOW:
			GPIO_write(GPIOB, 0, 1);
			show_config();
			break;
		case ST_CONFIG:
			GPIO_write(GPIOB, 0, 1);
			read_config();
			break;
		}
	}
}

// tasto 'X'
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_isset(EXTI10)) {
		switch (current_state) {
		case ST_RUN:
			current_state = ST_MENU;
			current_menu = 0;
			break;
		case ST_MENU:
			current_menu = (current_menu + 1) % 3;
			break;
		case ST_CONFIG:
			switch(current_menu) {
			case 0: current_time = adc_time; break;
			case 1: on_time = adc_time; break;
			case 2: off_time = adc_time; break;
			}
			current_state = ST_SHOW;
			break;
		}
		EXTI_clear(EXTI10);
	}
}

// tasto 'Y'
void EXTI4_IRQHandler(void)
{
	if (EXTI_isset(EXTI4)) {
		switch (current_state) {
		case ST_MENU:
			current_state = ST_RUN;
			break;
		case ST_SHOW:
			current_state = ST_MENU;
			break;
		case ST_CONFIG:
			current_state = ST_SHOW;
			break;
		}
		EXTI_clear(EXTI4);
	}
}

// tasto 'Z' & 'T'
void EXTI9_5_IRQHandler(void)
{
	 //'Z'
	if (EXTI_isset(EXTI5)) {
		switch(current_state) {
		case ST_MENU:
			current_state = ST_SHOW;
			break;
		case ST_SHOW:
			current_state = ST_CONFIG;
			break;
		}
		EXTI_clear(EXTI5);
	}
	 //'T'
	if (EXTI_isset(EXTI6)) {
		EXTI_clear(EXTI6);
	}
}


int time_ge(t_time * t1, t_time * t2)
{
	if (t1->mm > t2->mm) return 1;
	else if (t1->mm == t2->mm && t1->ss >= t2->ss) return 1;
	else return 0;
}


void TIM2_IRQHandler(void)
{
	if (TIM_update_check(TIM2)) {
		current_time.ss++;
		if (current_time.ss == 60) {
			current_time.ss = 0;
			current_time.mm = (current_time.mm + 1) % 60;
		}

		if (current_state == ST_RUN && on_time.configured && off_time.configured) {
			if (time_ge(&current_time, &on_time) && time_ge(&off_time, &current_time))
				GPIO_write(GPIOC, 2, 1);
			else
				GPIO_write(GPIOC, 2, 0);
		}

		TIM_update_clear(TIM2);
	}
}
