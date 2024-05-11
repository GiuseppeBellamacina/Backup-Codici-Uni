#include "stm32_unict_lib.h"
#include <stdio.h>

enum {
	OFF,
	ON,
	SETUP
};

int state = OFF;
int delay_count;
int timeout_value = 10;

void setup(void)
{
	DISPLAY_init();

	GPIO_init(GPIOB);
	GPIO_config_output(GPIOB, 0);

	GPIO_init(GPIOC);
	GPIO_config_output(GPIOC, 2);

	GPIO_config_input(GPIOB, 10);
	GPIO_config_EXTI(GPIOB, EXTI10);
	EXTI_enable(EXTI10, FALLING_EDGE);

	GPIO_config_input(GPIOB, 4);
	GPIO_config_EXTI(GPIOB, EXTI4);
	EXTI_enable(EXTI4, FALLING_EDGE);

	GPIO_config_input(GPIOB, 5);
	GPIO_config_EXTI(GPIOB, EXTI5);
	EXTI_enable(EXTI5, FALLING_EDGE);

}

void EXTI4_IRQHandler(void)
{
	if (EXTI_isset(EXTI4)) {
		// tasto Y
		switch(state) {
		case ON:
			// spengi luce
			GPIO_write(GPIOB, 0, 0);
			state = OFF;
			break;
		case SETUP:
			if (timeout_value < 60)
				++timeout_value;
			break;
		}
		EXTI_clear(EXTI4);
	}
}


void EXTI9_5_IRQHandler(void)
{
	if (EXTI_isset(EXTI5)) {
		// tasto Z
		switch(state) {
		case  OFF:
			GPIO_write(GPIOC, 2, 1);
			state = SETUP;
			break;
		case SETUP:
			GPIO_write(GPIOC, 2, 0);
			state = OFF;
			break;
		}
		EXTI_clear(EXTI5);
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
		case SETUP:
			if (timeout_value > 5)
				--timeout_value;
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
		delay_ms(10);
		++delay_count;
		if (delay_count == timeout_value * 100) {
			state = OFF;
			GPIO_write(GPIOB, 0, 0);
		}
		int seconds = delay_count / 100;
		sprintf(s,"%4d",seconds);
		DISPLAY_puts(0, s);
		break;
	case SETUP:
		sprintf(s,"%4d",timeout_value);
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
