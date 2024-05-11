/*
 * imu.c
 *
 *  Created on: Nov 26, 2018
 *      Author: corrado
 */

#include "stm32_unict_lib.h"
#include <stdio.h>
#include <stdlib.h>

enum {
	IDLE,
	START,
	BIT,
	CLOCK,
	STOP
};

struct mat_state_t {
	int state;
	int bit_count;
	int data;
} mat_state;

void MAT_init(void)
{
	GPIO_init(GPIOA);
	GPIO_config_output(GPIOA, 5); // PA5 = CLK
	GPIO_config_output(GPIOA, 6); // PA6 = LOAD/nCS
	GPIO_config_output(GPIOA, 7); // PA7 = DATA

	GPIO_write(GPIOA, 6, 1);
	GPIO_write(GPIOA, 5, 0);
	GPIO_write(GPIOA, 7, 0);

	mat_state.state = IDLE;

	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 84, 1);
	TIM_enable_irq(TIM2, IRQ_UPDATE);
	TIM_set(TIM2, 0);
	TIM_on(TIM2);
}

void TIM2_IRQHandler(void)
{
	if (TIM_update_check(TIM2)) {
		switch(mat_state.state) {
		case IDLE:
			GPIO_write(GPIOA, 6, 1);
			GPIO_write(GPIOA, 5, 0);
			GPIO_write(GPIOA, 7, 0);
			break;
		case START:
			GPIO_write(GPIOA, 6, 0);
			mat_state.state = BIT;
			mat_state.bit_count = 0;
			break;
		case BIT:
			GPIO_write(GPIOA, 5, 0);
			// emit bit
			if (mat_state.bit_count == 16) {
				mat_state.state = STOP;
			}
			else {
				if ( (mat_state.data & 0x8000) != 0)
					GPIO_write(GPIOA, 7, 1);
				else
					GPIO_write(GPIOA, 7, 0);
				mat_state.data = mat_state.data << 1;
				mat_state.bit_count++;
				mat_state.state = CLOCK;
			}
			break;
		case CLOCK:
			GPIO_write(GPIOA, 5, 1);
			mat_state.state = BIT;
			break;
		case STOP:
			GPIO_write(GPIOA, 6, 1);
			GPIO_write(GPIOA, 5, 0);
			GPIO_write(GPIOA, 7, 0);
			mat_state.state = IDLE;
			break;
		}
		TIM_update_clear(TIM2);
	}
}

void MAT_write(uint16_t data)
{
	// wait that previous transmission is finished
	while (mat_state.state != IDLE) {}
	mat_state.data = data;
	mat_state.state = START;
}

int main(void)
{
	CONSOLE_init();
	MAT_init();
	MAT_write(0x0C01);
	MAT_write(0x0900);
	MAT_write(0x0b07);
	MAT_write(0x0a0f);

	MAT_write(0x0100);
	MAT_write(0x027e);
	MAT_write(0x0342);
	MAT_write(0x0442);
	MAT_write(0x0542);
	MAT_write(0x0642);
	MAT_write(0x077e);
	MAT_write(0x08ff);

	for(;;) { }

//	for (;;) {
//		MAT_write(0x0181);
//		MAT_write(0x0242);
//		MAT_write(0x0324);
//		MAT_write(0x0418);
//		MAT_write(0x0518);
//		MAT_write(0x0624);
//		MAT_write(0x0742);
//		MAT_write(0x0881);
//		delay_ms(100);
//		MAT_write(0x0100);
//		MAT_write(0x0200);
//		MAT_write(0x0300);
//		MAT_write(0x0400);
//		MAT_write(0x0500);
//		MAT_write(0x0600);
//		MAT_write(0x0700);
//		MAT_write(0x0800);
//		delay_ms(100);
//	}
}
