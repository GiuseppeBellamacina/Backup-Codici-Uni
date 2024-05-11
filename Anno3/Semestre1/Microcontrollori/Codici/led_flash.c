#include "stm32_unict_lib.h"

void setup(void)
{
	GPIO_init(GPIOB);
	GPIO_config_output(GPIOB, 0);
}

void loop(void)
{
	GPIO_write(GPIOB, 0, 1);
	delay_ms(500);
	GPIO_write(GPIOB, 0, 0);
	delay_ms(500);
}

int main()
{
	setup();
	for(;;) {
		loop();
	}
	return 0;
}
