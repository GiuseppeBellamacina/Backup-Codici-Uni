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
	GPIO_config_input(GPIOB, 5);
	GPIO_write(GPIOB, 8, 1);
	GPIO_write(GPIOB, 9, 1);
	for(;;) {
		// lettura PB5
		int pinvalue = GPIOB->IDR & (1 << 5);
		if (pinvalue == 0) {
			// pulsante premuto, accendi PB0
			GPIOB->ODR |= 1;
		}
		else {
			// pulsante rilasciato, spegni PB0
			GPIOB->ODR &= ~1;
		}
	}
	return 0;
}
