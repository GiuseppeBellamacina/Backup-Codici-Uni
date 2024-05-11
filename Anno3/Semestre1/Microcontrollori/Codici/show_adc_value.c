#include "stm32_unict_lib.h"
#include <stdio.h>

void setup(void)
{
	DISPLAY_init();

	ADC_init(ADC1, ADC_RES_12, ADC_ALIGN_RIGHT);
	ADC_channel_config(ADC1, GPIOC, 0, 10);
	ADC_on(ADC1);

	ADC_sample_channel(ADC1, 10);
}

 void loop(void)
{
	 char s[5];
	 ADC_start(ADC1);
	 while (!ADC_completed(ADC1)) {}

	 int adcvalue = ADC_read(ADC1);
	 sprintf(s,"%4d", adcvalue);
	 DISPLAY_puts(0,s);
}

int main()
{
	setup();
	for(;;) {
		loop();
	}
	return 0;
}
