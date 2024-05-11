/*
 * getstring.c
 *
 *  Created on: Nov 19, 2018
 *      Author: corrado
 */

#include "stm32_unict_lib.h"
#include <stdio.h>
#include <string.h>


void getstring(char * s, int maxlen)
{
	int i = 0;
	for (;;) {
		char c = readchar();
		if (c == 13) {
			printf("\n");
			s[i] = 0;
			return;
		}
		else if (c == 8) {
			if (i > 0) {
				--i;
				__io_putchar(8); // BS
				__io_putchar(' '); // SPAZIO
				__io_putchar(8); // BS
			}
		}
		else if (c >= 32) { // il carattere appartiene al set stampabile
			if (i < maxlen) {
				__io_putchar(c); // echo del carattere appena inserito
				// inserisci il carattere nella stringa
				s[i] = c;
				i++;
			}
		}
	}
}

int main(void)
{
	CONSOLE_init();

	for (;;) {
		char s[20];
		int i;
		printf("Inserisci una stringa:");
		fflush(stdout);
		getstring(s, 19);
		printf("Stringa inserita: %s\n", s);
		for (i = 0; i < strlen(s);i++) {
			printf("%d ", s[i]);
		}
		printf("\n");
	}
}
