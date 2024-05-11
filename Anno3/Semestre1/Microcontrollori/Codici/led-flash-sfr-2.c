/*
 * led_flash.c
 *
 *  Created on: Oct 3, 2018
 *      Author: corrado
 */

#include "stm32_unict_lib.h"

int main(void)
{
	RCC->AHB1ENR |= (1 << 1); // bit 1

	GPIOB->MODER = (GPIOB->MODER & 0xfffd) | 1;
	GPIOB->OTYPER = GPIOB->OTYPER & 0xfffe;
	GPIOB->OSPEEDR = GPIOB->OSPEEDR & 0xfffc;

	for(;;) {
		GPIOB->BSRR = 1;
		delay_ms(500);
		GPIOB->BSRR = 1 << 16;
		delay_ms(500);
	}
	return 0;
}
