/*
 * test-uart.c
 *
 *  Created on: Nov 12, 2018
 *      Author: corrado
 */

#include "stm32_unict_lib.h"
#include <stdio.h>

int main(void)
{
	CONSOLE_init();
	DISPLAY_init();

	for (;;) {
		printf("Hello, world!\n");
		delay_ms(1000);
		if (kbhit()) {
			char s[5];
			char c = readchar();
			sprintf(s, "%4x", c);
			DISPLAY_puts(0, s);
		}
	}
}
