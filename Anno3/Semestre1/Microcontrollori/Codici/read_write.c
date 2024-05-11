#include "stm32_unict_lib.h"

void setup(void)
{
	GPIO_init(GPIOB);
	GPIO_config_output(GPIOB, 0);
	GPIO_config_input(GPIOB, 10);
}

void loop(void)
{
	int pinval = !GPIO_read(GPIOB, 10);
	GPIO_write(GPIOB, 0, pinval);
}

int main()
{
	setup();
	for(;;) {
		loop();
	}
	return 0;
}
