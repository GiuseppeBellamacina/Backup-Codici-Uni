/*
 * led_flash.c
 *
 *  Created on: Oct 3, 2018
 *      Author: corrado
 */

#include "stm32_unict_lib.h"

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	// enable clock to GPIOB
	GPIOB->MODER = (GPIOB->MODER & ~(int32_t)2) | 1;
	// PB0 in output mode, MODER0 = 01
	GPIOB->OTYPER &= ~(int32_t)1;
	// PB0 in push-pull mode
	GPIOB->OSPEEDR &= ~(int32_t)3;
	// PB0 in low speed mode
	GPIOB->PUPDR &= ~(int32_t)3;
	// PB0 no pull-up, no pull-down
	for (;;) {
		GPIOB->ODR ^= 1;
		// toggle PB0
		delay_ms(100);
	}
	return 0;
}

