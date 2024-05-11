/*
 * led_flash.c
 *
 *  Created on: Oct 3, 2018
 *      Author: corrado
 */

#include <stdio.h>
#include "stm32_unict_lib.h"

int main(void)
{
	DISPLAY_init();
	GPIO_init(GPIOB);
	GPIO_config_output(GPIOB, 0);
	GPIO_config_output(GPIOB, 8);
	GPIO_config_output(GPIOB, 9);
	GPIO_config_input(GPIOB, 4);
	GPIO_config_input(GPIOB, 5);
	GPIO_config_input(GPIOB, 6);
	GPIO_config_input(GPIOB, 10);
	GPIO_write(GPIOB, 8, 1);
	GPIO_write(GPIOB, 9, 1);
	for(;;) {
		char s[5];
		sprintf(s, "%04x", (int)GPIOB->IDR);
		DISPLAY_puts(0, s);
	}
	return 0;
}
