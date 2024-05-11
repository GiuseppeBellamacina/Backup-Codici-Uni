#include "stm32_unict_lib.h"
#include <stdio.h>

enum {
	IDLE,
	EROG,
	STOP
};

int state = IDLE;
int importo = 0;
int flash_count;
float importo_erogato;

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

	GPIO_config_input(GPIOB, 6);
	GPIO_config_EXTI(GPIOB, EXTI6);
	EXTI_enable(EXTI6, FALLING_EDGE);

}

void EXTI4_IRQHandler(void)
{
	if (EXTI_isset(EXTI4)) {
		// tasto Y
		switch(state) {
		case IDLE:
			if (importo < 95)
				importo += 5;
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
		case IDLE:
			importo = 0;
			break;
		}
		EXTI_clear(EXTI5);
	}
	if (EXTI_isset(EXTI6)) {
		// tasto T
		switch(state) {
		case IDLE:
			importo_erogato = 0;
			flash_count = 0;
			state = EROG;
			break;
		case STOP:
			GPIO_write(GPIOB,0,0);
			importo = 0;
			state = IDLE;
			break;
		}
		EXTI_clear(EXTI6);
	}
}


void EXTI15_10_IRQHandler(void)
{
	if (EXTI_isset(EXTI10)) {
		// tasto X
		switch(state) {
		case IDLE:
			if (importo < 79)
				importo += 20;
			break;
		}
		EXTI_clear(EXTI10);
	}
}

void loop(void)
{
	char s[5];
	switch(state) {
	case IDLE:
		sprintf(s,"%2d00", importo);
		DISPLAY_puts(0,s);
		DISPLAY_dp(1,1);
		break;
	case EROG:
		delay_ms(10);
		++flash_count;
		if (flash_count == 50) {
			GPIO_toggle(GPIOC,2);
			flash_count = 0;
		}
		importo_erogato += 0.0075;
		sprintf(s,"%4d", (int)(importo_erogato*100));
		DISPLAY_puts(0,s);
		DISPLAY_dp(1,1);
		if (importo_erogato >= importo) {
			GPIO_write(GPIOC,2,0);
			GPIO_write(GPIOB,0,1);
			state = STOP;
		}
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
