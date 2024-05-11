/*
 * test_6.c
 *
 *  Created on: Jan 21, 2019
 *      Author: corrado
 */

#include "stm32_unict_lib.h"
#include <stdio.h>

int numero_assegnato = 0;
int numero_servito = 0;
int seconds = 0;
float attesa_media = 0;
int rilascio_numero = 0;
int nuovo_servizio = 0;

void main(void)
{
	DISPLAY_init();
	CONSOLE_init();
	GPIO_init(GPIOB);
	GPIO_config_input(GPIOB, 10);
	GPIO_config_input(GPIOB, 4);
	GPIO_config_output(GPIOB, 0);
	GPIO_config_EXTI(GPIOB, EXTI10);
	GPIO_config_EXTI(GPIOB, EXTI4);
	EXTI_enable(EXTI10, FALLING_EDGE);
	EXTI_enable(EXTI4, FALLING_EDGE);

	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 42000, 2000); // 1 sec
	TIM_set(TIM2, 0);
	TIM_enable_irq(TIM2, IRQ_UPDATE);
	TIM_on(TIM2);

	printf("Start\n");
	for (;;) {
		char s[5];
		if (rilascio_numero == 1) {
			rilascio_numero = 0;
			GPIO_write(GPIOB, 0, 1);
			numero_assegnato++;
			printf("Assegnato numero %d\n", numero_assegnato);
			if (numero_servito <= 1)
				sprintf(s, "%02d--", (numero_assegnato % 100));
			else
				sprintf(s, "%02d%02d", (numero_assegnato % 100), (int)attesa_media);
			DISPLAY_puts(0, s);
			delay_ms(500);
			DISPLAY_puts(0, "    ");
			delay_ms(500);
			DISPLAY_puts(0, s);
			delay_ms(500);
			DISPLAY_puts(0, "    ");
			delay_ms(500);
			GPIO_write(GPIOB, 0, 0);
		}
		else {
			if (numero_servito <= 1)
				sprintf(s, "%02d--", (numero_servito % 100));
			else
				sprintf(s, "%02d%02d", (numero_servito % 100), (int)attesa_media);
			DISPLAY_puts(0, s);
		}
		if (nuovo_servizio == 1) {
			if (numero_servito < numero_assegnato) {
				attesa_media = (attesa_media + seconds) / 2;
				seconds = 0;
				numero_servito++;
				printf("Adesso serviamo il numero %d\n", numero_servito);
			}
			nuovo_servizio = 0;
		}
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_update_check(TIM2)) {
		if (numero_servito < numero_assegnato)
			seconds ++;
		TIM_update_clear(TIM2);
	}
}

void EXTI4_IRQHandler(void)
{
	if (EXTI_isset(EXTI4)) {
		nuovo_servizio = 1;
		EXTI_clear(EXTI4);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_isset(EXTI10)) {
		rilascio_numero = 1;
		EXTI_clear(EXTI10);
	}
}
