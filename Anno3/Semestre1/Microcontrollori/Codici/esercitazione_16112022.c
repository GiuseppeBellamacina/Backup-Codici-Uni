/*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32_unict_lib.h"

enum {
	OFF,
	ON,
	PRE_OFF
};

typedef struct {
	int stato;
	int timer;
	int t_on;
	int flash_counter;
} t_fsm;

t_fsm ingresso, salone, cucina;
int in_config = 0;
int to_seconds = 0;

int T_l1 = 40; // 400ms
int T_l2 = 15; // 150ms

void getstring(char * s, int maxlen)
{
        int i = 0;
        for (;;) {
                char c = readchar();
                if (c >= 32) {
                        if (i < maxlen - 1) {
                                __io_putchar(c);
                                s[i] = c;
                                i++;
                        }
                }
                else {
                        switch(c) {
                        case 13: // Carriage Return
                                __io_putchar(c);
                                __io_putchar(10); // Line Feed
                                s[i] = 0;
                                return;
                        case 8: // Backspace
                                if (i > 0) {
                                        __io_putchar(c);
                                        __io_putchar(' ');
                                        __io_putchar(c);
                                        --i;
                                }
                                break;
                        }
                }
        }
}


void init_fsm(t_fsm * m, int _t_on)
{
	m->stato = OFF;
	m->timer = 0;
	m->t_on = _t_on;
	m->flash_counter = 0;
}

void pushbutton(t_fsm * m)
{
	m->stato = ON;
	m->timer = 0;
	m->flash_counter = 0;
}

int one_second(t_fsm * m)
{
	++m->timer;
	switch (m->stato) {
	case ON:
		if (m->timer >= (m->t_on - 4)) {
			m->stato = PRE_OFF;
		}
		break;
	case PRE_OFF:
		if (m->timer >= m->t_on) {
			m->stato = OFF;
			return 1;
		}
		break;
	}
	return 0;
}

int do_flash(t_fsm * m)
{
	++m->flash_counter;
	switch(m->stato) {
	case ON:
		if (m->flash_counter >= T_l1) {
			m->flash_counter = 0; // toggle LED
			return 1;
		}
		break;
	case PRE_OFF:
		if (m->flash_counter >= T_l2) {
			m->flash_counter = 0; // toggle LED
			return 1;
		}
		break;
	}
	return 0;
}

void setup(void)
{
	init_fsm(&ingresso, 8);
	init_fsm(&salone, 10);
	init_fsm(&cucina, 12);

    DISPLAY_init();
    CONSOLE_init();

    GPIO_init(GPIOB);
    GPIO_init(GPIOC);
    GPIO_config_output(GPIOB, 0);
    GPIO_config_output(GPIOC, 2);
    GPIO_config_output(GPIOC, 3);

    GPIO_config_input(GPIOB, 10);
    GPIO_config_EXTI(GPIOB, EXTI10);
    EXTI_enable(EXTI10, FALLING_EDGE);

    GPIO_config_input(GPIOB, 4);
    GPIO_config_EXTI(GPIOB, EXTI4);
    EXTI_enable(EXTI4, FALLING_EDGE);

    GPIO_config_input(GPIOB, 5);
    GPIO_config_EXTI(GPIOB, EXTI5);
    EXTI_enable(EXTI5, FALLING_EDGE);

    GPIO_config_input(GPIOB, 6);
    GPIO_config_EXTI(GPIOB, EXTI6);
    EXTI_enable(EXTI6, FALLING_EDGE);

    TIM_init(TIM2);
    TIM_config_timebase(TIM2, 84, 10000);
    TIM_enable_irq(TIM2, IRQ_UPDATE);
    TIM_on(TIM2);

    ADC_init(ADC1, ADC_RES_6, ADC_ALIGN_RIGHT);
    ADC_channel_config(ADC1, GPIOC, 0, 10);
    ADC_channel_config(ADC1, GPIOC, 1, 11);
    ADC_on(ADC1);

}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_isset(EXTI10)) {
		if (!in_config)
			pushbutton(&ingresso);
		EXTI_clear(EXTI10);
	}
}

void EXTI4_IRQHandler(void)
{
	if (EXTI_isset(EXTI4)) {
		if (!in_config)
			pushbutton(&salone);
		EXTI_clear(EXTI4);
	}
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI_isset(EXTI5)) {
		if (!in_config)
			pushbutton(&cucina);
		EXTI_clear(EXTI5);
	}
	if (EXTI_isset(EXTI6)) {
		if (ingresso.stato == OFF && salone.stato == OFF && cucina.stato == OFF) {
			in_config = 1;
		}
		EXTI_clear(EXTI6);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_update_check(TIM2)) {
		// IRQ ogni 10ms
		++to_seconds;
		if (to_seconds >= 100) {
			to_seconds = 0;
			if (one_second(&ingresso)) GPIO_write(GPIOB, 0, 0);
			if (one_second(&cucina)) GPIO_write(GPIOC, 2, 0);
			if (one_second(&salone)) GPIO_write(GPIOC, 3, 0);
		}
		if (do_flash(&ingresso)) GPIO_toggle(GPIOB, 0);
		if (do_flash(&salone)) GPIO_toggle(GPIOC, 2);
		if (do_flash(&cucina)) GPIO_toggle(GPIOC, 3);
		TIM_update_clear(TIM2);
	}
}

void do_configuration(void)
{
	for (;;) {
		char scelta[10];
		int v;
		printf("0- Fine\n");
		printf("1- Imposta TI\n");
		printf("2- Imposta TS\n");
		printf("3- Imposta TC\n");
		getstring(scelta,10);
		switch(scelta[0]) {
		case '0':
			return;
		case '1':
			printf("Inserisci TI:");
			fflush(stdout);
			getstring(scelta,10);
			v = atoi(scelta);
			if (v < 5 || v > 20)
				printf("Errore! Inserire un valore nell'intervallo 5-20\n");
			else
				ingresso.t_on = v;
			break;
		case '2':
			printf("Inserisci TS:");
			fflush(stdout);
			getstring(scelta,10);
			v = atoi(scelta);
			if (v < 5 || v > 20)
				printf("Errore! Inserire un valore nell'intervallo 5-20\n");
			else
				salone.t_on = v;
			break;
		case '3':
			printf("Inserisci TC:");
			fflush(stdout);
			getstring(scelta,10);
			v = atoi(scelta);
			if (v < 5 || v > 20)
				printf("Errore! Inserire un valore nell'intervallo 5-20\n");
			else
				cucina.t_on = v;
			break;
		}
	}
}

void loop(void)
{
	char s[5];

	if (in_config) {
		do_configuration();
		in_config = 0;
	}

	strcpy(s, "    ");
	if (ingresso.stato != OFF) s[0] = 'I';
	if (salone.stato != OFF) s[1] = 'S';
	if (cucina.stato != OFF) s[2] = 'C';
	DISPLAY_puts(0,s);

	ADC_sample_channel(ADC1, 11);
	ADC_start(ADC1);
    while (!ADC_completed(ADC1)) {}
    int adc_t_l1 = ADC_read(ADC1);

	ADC_sample_channel(ADC1, 10);
	ADC_start(ADC1);
    while (!ADC_completed(ADC1)) {}
    int adc_t_l2 = ADC_read(ADC1);

    T_l1 = (adc_t_l1 * 20) / 63 + 30;
    T_l2 = (adc_t_l2 * 10) / 63 + 10;
}


int main(void)
{
	setup();
	while (1) { loop(); }
	return 1;
}
