#include "stm32_unict_lib.h"
#include <stdio.h>

enum {
	OFF,
	ON,
	CONFIG
};

int state = OFF;
int delay_count;
int new_time;
int on_time = 10;

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

	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 8400, 10000);
	TIM_enable_irq(TIM2, IRQ_UPDATE);
	TIM_on(TIM2);

    ADC_init(ADC1, ADC_RES_6, ADC_ALIGN_RIGHT);
    ADC_channel_config(ADC1, GPIOC, 0, 10);
    ADC_on(ADC1);
    ADC_sample_channel(ADC1, 10);
}

void TIM2_IRQHandler(void)
{
	if (TIM_update_check(TIM2)) {

		if (state == ON) {
			++delay_count;
			if (delay_count == on_time) {
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

void EXTI9_5_IRQHandler(void)
{
	if (EXTI_isset(EXTI5)) {
		switch(state) {
		case OFF:
			state = CONFIG;
			GPIO_write(GPIOC,2,1);
			break;
		case CONFIG:
			state = OFF;
			on_time = new_time;
			GPIO_write(GPIOC,2,0);
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
	case CONFIG:
		ADC_start(ADC1);
		while (!ADC_completed(ADC1)) {}
		// [0,63] --> [10, 20]
		new_time = ADC_read(ADC1) / 63.0 * (20 - 10) + 10;
		sprintf(s,"%4d",new_time);
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
