#include "stm32_unict_lib.h"
#include <stdio.h>

enum {
	OFF,
	ON
};

int state = OFF;
int delay_count;

void setup(void)
{
	DISPLAY_init();

	GPIO_init(GPIOB);
	GPIO_config_output(GPIOB, 0);

	GPIO_config_input(GPIOB, 10);
	GPIO_config_EXTI(GPIOB, EXTI10);
	EXTI_enable(EXTI10, FALLING_EDGE);

	GPIO_config_input(GPIOB, 4);
	GPIO_config_EXTI(GPIOB, EXTI4);
	EXTI_enable(EXTI4, FALLING_EDGE);

	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 8400, 10000);
	TIM_enable_irq(TIM2, IRQ_UPDATE);
	TIM_on(TIM2);

}

void TIM2_IRQHandler(void)
{
	if (TIM_update_check(TIM2)) {

		if (state == ON) {
			++delay_count;
			if (delay_count == 10) {
				state = OFF;
				GPIO_write(GPIOB, 0, 0);
			}
		}

		TIM_update_clear(TIM2);
	}
}

void EXTI4_IRQHandler(void)
{
	if (EXTI_isset(EXTI4)) {
		if (state == ON) {
			// spengi luce
			GPIO_write(GPIOB, 0, 0);
			state = OFF;
		}
		EXTI_clear(EXTI4);
	}
}


void EXTI15_10_IRQHandler(void)
{
	if (EXTI_isset(EXTI10)) {
		// tasto X premuto
		switch(state) {
		case OFF:
			state = ON;
			// accendere luce, avviare timer
			GPIO_write(GPIOB, 0, 1);
			delay_count = 0;
			break;
		case ON:
			state = ON;
			// riavviare timer
			delay_count = 0;
			break;
		}
		EXTI_clear(EXTI10);
	}
}

void loop(void)
{
	char s[5];
	switch(state) {
	case ON:
		sprintf(s,"%4d",delay_count);
		DISPLAY_puts(0, s);
		break;
	}

}

int main()
{
	setup();
	for(;;) {
		loop();
	}
	return 0;
}
