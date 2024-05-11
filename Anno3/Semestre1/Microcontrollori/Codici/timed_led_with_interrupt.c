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
	switch(state) {
	case ON:
		delay_ms(10);
		++delay_count;
		if (delay_count == 1000) {
			state = OFF;
			GPIO_write(GPIOB, 0, 0);
		}
		int seconds = delay_count / 100;
		char s[5];
		sprintf(s,"%4d",seconds);
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
