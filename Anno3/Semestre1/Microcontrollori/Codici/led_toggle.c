#include "stm32_unict_lib.h"

int state = 0;
int last_pin_state;

void setup(void)
{
	GPIO_init(GPIOB);
	GPIO_config_output(GPIOB, 0);
	GPIO_config_input(GPIOB, 10);
	last_pin_state = GPIO_read(GPIOB, 10);
}

void loop(void)
{
	int pinval = GPIO_read(GPIOB, 10);
	if (last_pin_state == 1 && pinval == 0) {
		// pushbutton pressed
		state = !state;
		GPIO_write(GPIOB, 0, state);
	}
	last_pin_state = pinval;
}

int main()
{
	setup();
	for(;;) {
		loop();
	}
	return 0;
}
