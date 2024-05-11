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

typedef void (*command_handler)(char **);

typedef struct {
	char * command;
	int num_param;
	command_handler handler;
} command_structure;

int period = 858;

void handle_period(char ** token)
{
	period = atoi(token[1]);
	TIM3->ARR = period;
}

void handler_duty(char ** token)
{
	int duty = atoi(token[1]);
	int new_Ton = (duty * period) / 100;
	TIM3->CCR3 = new_Ton;
}

command_structure commands[] = {
		{ "period", 2, handle_period },
		{ "duty", 2, handler_duty },
		{ NULL, 0, NULL}
};


int main(void)
{
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
			char * token[20];
			char * p;
			int token_count = 1;
			token[0] = strtok(s, " ");
			while ( (p = strtok(NULL, " ")) != NULL) {
				token[token_count] = p;
				token_count++;
				if (token_count == 20)
					break;
			}

			int i = 0;
			int command_index = -1;
			while (commands[i].command != NULL) {
				if (strcmp(token[0], commands[i].command) == 0
						&& token_count >= commands[i].num_param) {
					command_index = i;
					break;
				}
				i++;
			}

			if (command_index >= 0) {
				commands[command_index].handler(token);
			}
			else {
				printf("comando non valido\n");
			}
		}
	}
}
