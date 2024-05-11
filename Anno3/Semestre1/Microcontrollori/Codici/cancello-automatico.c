/*
 * cancello-automatico.c
 *
 *  Created on: Oct 17, 2018
 *      Author: corrado
 */

#include "stm32_unict_lib.h"

enum {
	st_IDLE,
	st_APERTURA,
	st_ATTESA,
	st_CHIUSURA
};

int stato = st_IDLE;

#define TC		20		// = 10 secondi
#define TA		8		// = 8 secondi

int timer_tc = 0;
int timer_ta = 0;

void main(void)
{
    GPIO_init(GPIOB);
    DISPLAY_init();

    GPIO_config_output(GPIOB, 0);

    GPIO_config_input(GPIOB, 10);
    GPIO_config_input(GPIOB, 4);
    GPIO_config_input(GPIOB, 5);

    GPIO_config_EXTI(GPIOB, EXTI10);
    EXTI_enable(EXTI10, FALLING_EDGE); // X

    GPIO_config_EXTI(GPIOB, EXTI4);
    EXTI_enable(EXTI4, FALLING_EDGE); // Y

    GPIO_config_EXTI(GPIOB, EXTI5);
    EXTI_enable(EXTI5, FALLING_EDGE); // Z

    TIM_init(TIM2);

    // Configure the timebase
    // Counter clock set to 0.1 ms
    TIM_config_timebase(TIM2, 8400, 5000);

    TIM_set(TIM2, 0); // resets the counter
    TIM_on(TIM2); // starts the timer

    TIM_enable_irq(TIM2, IRQ_UPDATE);

    for (;;) {
    	switch(stato) {
    	case st_IDLE:
    		DISPLAY_puts(0, "----");
    		break;
    	default:
    		if (timer_tc < 5)
        		DISPLAY_puts(0, "----");
    		else if (timer_tc < 10)
    			DISPLAY_puts(0, "--- ");
    		else if (timer_tc < 15)
    			DISPLAY_puts(0, "-- ");
    		else if (timer_tc < 19)
    			DISPLAY_puts(0, "-  ");
    		else
    			DISPLAY_puts(0, "   ");
    		break;
    	}
    }

}


void TIM2_IRQHandler(void)
{
	// check the update event
	if (TIM_update_check(TIM2)) {
		switch (stato) {
		case st_IDLE:
			GPIO_write(GPIOB, 0, 0);
			break;
		case st_APERTURA:
			GPIO_toggle(GPIOB, 0);
			++timer_tc;
			if (timer_tc >= TC) {
				stato = st_ATTESA;
				timer_ta = 0;
			}
			break;
		case st_ATTESA:
			GPIO_toggle(GPIOB, 0);
			++timer_ta;
			if (timer_ta >= TA) {
				stato = st_CHIUSURA;
			}
			break;
		case st_CHIUSURA:
			GPIO_toggle(GPIOB, 0);
			--timer_tc;
			if (timer_tc < 0) {
				stato = st_IDLE;
			}
			break;
		}
		TIM_update_clear(TIM2);
	}
}

// tasto 'X'
void EXTI15_10_IRQHandler(void)
{
	if (EXTI_isset(EXTI10)) {
		switch (stato) {
		case st_IDLE:
			stato = st_APERTURA;
			timer_tc = 0;
			break;
		case st_CHIUSURA:
			stato = st_APERTURA;
			break;
		}
		EXTI_clear(EXTI10);
	}
}

// tasto 'Y'
void EXTI4_IRQHandler(void)
{
	if (EXTI_isset(EXTI4)) {
		switch(stato) {
		case st_ATTESA:
			stato = st_CHIUSURA;
			break;
		}
		EXTI_clear(EXTI4);
	}
}

// tasto 'Z'
void EXTI9_5_IRQHandler(void)
{
	if (EXTI_isset(EXTI5)) { //'Z'
		switch(stato) {
		case st_ATTESA:
			timer_ta = 0;
			break;
		case st_CHIUSURA:
			stato = st_APERTURA;
			break;
		}
		EXTI_clear(EXTI5);
	}
}
