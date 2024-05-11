#include "stm32_unict_lib.h"

enum {
	OFF,
	ON
};

int state = OFF;
int last_pin_state;
int delay_count;

void setup(void)
{
	GPIO_init(GPIOB);
	GPIO_config_output(GPIOB, 0);
	GPIO_config_input(GPIOB, 10);
	last_pin_state = GPIO_read(GPIOB, 10);
}

void loop(void)
{
	// input event check
	int pinval = GPIO_read(GPIOB, 10);
	if (last_pin_state == 1 && pinval == 0) {
		// pushbutton pressed
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
	}
	last_pin_state = pinval;

	switch(state) {
	case ON:
		delay_ms(10);
		++delay_count;
		if (delay_count == 1000) {
			state = OFF;
			GPIO_write(GPIOB, 0, 0);
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
