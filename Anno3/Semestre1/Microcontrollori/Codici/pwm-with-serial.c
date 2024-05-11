/*
 * getstring.c
 *
 *  Created on: Nov 19, 2018
 *      Author: corrado
 */

#include "stm32_unict_lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
	int period = 858;
	CONSOLE_init();
    GPIO_init(GPIOB);
    GPIO_config_alternate(GPIOB, 0, 2); // AF2 --> TIMER3, CH3

    TIM_init(TIM3);
    // f = 84MHz
    // PSC = 60000
    // frequenza di incremento = 84Mhz/60000 = 1400Hz
    // durata di un tick di incremento ~= 0.7ms
    // P = 600ms --> ~ 858 count
    TIM_config_timebase(TIM3, 60000, period);
    TIM_config_PWM(TIM3, 3); // TIMER3, CH3
    // Ton = 50ms -> ~ 72 count
    TIM3->CCR3 = 72;
    TIM_set(TIM3, 0);
    TIM_on(TIM3);

    __io_putchar(12); // clear screen
	for (;;) {
		char s[20];
		int i;
		printf("Inserisci il comando [?=help]:");
		fflush(stdout);
		getstring(s, 19);
		// period nuovo-periodo
		// duty percentuale
		if (strcmp(s, "?") == 0) {
			printf("period <valore>: imposta il periodo di lampeggio\n");
			printf("duty <valore%>: imposta il duty cycle (in percentuale)\n");
		}
		else {
			char * space_position = strchr(s, ' ');
			if (space_position != NULL) {
				*space_position = 0; // terminatore di stringa
				char * param = space_position + 1;
				//printf("Comando:%s\n", s);
				//printf("Parametro:%s\n", param);
				if (strcmp(s, "period") == 0) {
					period = atoi(param);
					TIM3->ARR = period;
				}
				else if (strcmp(s, "duty") == 0) {
					int duty = atoi(param);
					int new_Ton = (duty * period) / 100;
					TIM3->CCR3 = new_Ton;
				}
				else {
					printf("comando non valido\n");
				}
			}
		}
	}
}
