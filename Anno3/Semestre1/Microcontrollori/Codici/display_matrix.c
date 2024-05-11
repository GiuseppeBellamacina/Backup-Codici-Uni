/*
 * imu.c
 *
 *  Created on: Nov 26, 2018
 *      Author: corrado
 */

#include "stm32_unict_lib.h"
#include <stdio.h>
#include <stdlib.h>

void MAT_init(void)
{
	GPIO_init(GPIOA);
	GPIO_config_output(GPIOA, 5); //CLK
	GPIO_config_output(GPIOA, 6); //LOAD/nCS
	GPIO_config_output(GPIOA, 7); //DATA

	GPIO_write(GPIOA, 6, 1);
	GPIO_write(GPIOA, 5, 0);
	GPIO_write(GPIOA, 7, 0);
}

void MAT_write(uint16_t data)
{
	int i;
	GPIO_write(GPIOA, 6, 1);
	GPIO_write(GPIOA, 5, 0);
	GPIO_write(GPIOA, 7, 0);
	delay_ms(1);
	GPIO_write(GPIOA, 6, 0); // nCS = 0
	for (i = 0; i < 16;i++) {
		if ( (data & 0x8000) != 0)
			GPIO_write(GPIOA, 7, 1);
		else
			GPIO_write(GPIOA, 7, 0);
		delay_ms(1);
		GPIO_write(GPIOA, 5, 1);
		delay_ms(1);
		GPIO_write(GPIOA, 5, 0);
		data = data << 1;
	}
	GPIO_write(GPIOA, 6, 1); // nCS = 1
	delay_ms(1);
	GPIO_write(GPIOA, 5, 0);
	GPIO_write(GPIOA, 7, 0);
	delay_ms(10);
}

int main(void)
{
	CONSOLE_init();
	MAT_init();
	MAT_write(0x0C01);
	MAT_write(0x0900);
	MAT_write(0x0b07);
	MAT_write(0x0a07);

	for (;;) {
		MAT_write(0x0181);
		MAT_write(0x0242);
		MAT_write(0x0324);
		MAT_write(0x0418);
		MAT_write(0x0518);
		MAT_write(0x0624);
		MAT_write(0x0742);
		MAT_write(0x0881);
		delay_ms(100);
		MAT_write(0x0100);
		MAT_write(0x0200);
		MAT_write(0x0300);
		MAT_write(0x0400);
		MAT_write(0x0500);
		MAT_write(0x0600);
		MAT_write(0x0700);
		MAT_write(0x0800);
		delay_ms(100);
	}
}
