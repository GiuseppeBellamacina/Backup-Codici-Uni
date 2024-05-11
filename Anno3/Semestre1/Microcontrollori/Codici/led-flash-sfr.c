/*
 * led_flash.c
 *
 *  Created on: Oct 3, 2018
 *      Author: corrado
 */

#include "stm32_unict_lib.h"

int main(void)
{
	GPIO_init(GPIOB);
	GPIO_config_output(GPIOB, 0);
	GPIO_config_output(GPIOB, 8);
	GPIO_config_output(GPIOB, 9);
	GPIO_write(GPIOB, 8, 1);
	GPIO_write(GPIOB, 9, 1);
	for(;;) {
		GPIOB->ODR = GPIOB->ODR | 1;
		delay_ms(500);
		GPIOB->ODR = GPIOB->ODR & 0xfffe;
		delay_ms(500);
	}
	return 0;
}
