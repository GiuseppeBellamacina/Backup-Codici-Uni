#include "stm32_unict_lib.h"

enum {
	OFF,
	FLASHING
};

int state = OFF;
int last_pin_state;
int flash_count;

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
			flash_count = 0;
			state = FLASHING;
			break;
		case FLASHING:
			state = OFF;
			break;
		}
	}
	last_pin_state = pinval;

	// output update
	switch(state) {
	case OFF:
		GPIO_write(GPIOB, 0, 0);
		break;
	case FLASHING:
		delay_ms(10);
		++flash_count;
		if (flash_count == 50) {
			GPIO_toggle(GPIOB, 0);
			flash_count = 0;
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
