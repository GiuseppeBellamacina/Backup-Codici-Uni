#include "stm32_unict_lib.h"
#include <stdio.h>

void setup(void)
{
	DISPLAY_init();

	GPIO_init(GPIOB);
	GPIO_config_output(GPIOB, 0);

	TIM_init(TIM2);
	TIM_config_timebase(TIM2, 8400, 5000);
	TIM_enable_irq(TIM2, IRQ_UPDATE);
	TIM_on(TIM2);
}

void loop(void)
{
	char s[5];
	sprintf(s, "%4d", TIM2->CNT);
	DISPLAY_puts(0,s);
}

void TIM2_IRQHandler(void)
{
	if (TIM_update_check(TIM2)) {
		GPIO_toggle(GPIOB,0);
		TIM_update_clear(TIM2);
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
