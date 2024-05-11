/*
 * max6968.c
 *
 *  Created on: Jan 7, 2020
 *      Author: corrado
 */

#include "stm32_unict_lib.h"

/*
 * This led_panel example uses 3 IC MAX6968 as LED drivers
 *
 * GPIO MAPPING
 *
 * PA8  --> DATA
 * PB10 --> CLK
 * PB4  --> LE
 * PB5  --> OE1
 * PB3  --> OE2
 * PA10 --> OE3
 *
 */

uint8_t digit_map[10] = { 	0b11110110,
							0b01100000,
							0b11011010,
							0b11101010,
							0b01101100,
							0b10101110,
							0b10111110,
							0b01100010,
							0b11111110,
							0b11101110 };

void led_panel_init(void)
{
	GPIO_init(GPIOA);
	GPIO_init(GPIOB);
	GPIO_config_output(GPIOA, 8);
	GPIO_config_output(GPIOB, 10);
	GPIO_config_output(GPIOB, 4);
	GPIO_config_output(GPIOB, 5);
	GPIO_config_output(GPIOB, 3);
	GPIO_config_output(GPIOA, 10);
	// output enable OFF
	GPIO_write(GPIOB, 5, 1);
	GPIO_write(GPIOB, 3, 1);
	GPIO_write(GPIOA, 10, 1);
	// latch enable to 0
	GPIO_write(GPIOB, 4, 0);
	// clock to 0
	GPIO_write(GPIOB, 10, 0);
}

void led_panel_write_byte(uint8_t b)
{
	int i;
	for (i = 0 ; i < 8; i++) {
		if ((b & 0x80) != 0)
			GPIO_write(GPIOA, 8, 1); // out 1
		else
			GPIO_write(GPIOA, 8, 0); // out 0
		// clock pulse
		asm ( "nop" ); //~12 ns
		asm ( "nop" ); //~12 ns
		GPIO_write(GPIOB, 10, 1); // clock to high
		asm ( "nop" ); //~12 ns
		asm ( "nop" ); //~12 ns
		asm ( "nop" ); //~12 ns
		asm ( "nop" ); //~12 ns
		GPIO_write(GPIOB, 10, 0); // clock to low
		asm ( "nop" ); //~12 ns
		asm ( "nop" ); //~12 ns
		b = b << 1; // shift left the byte
	}
}

void led_panel_write(uint8_t b1, uint8_t b2, uint8_t b3)
{
	led_panel_write_byte(digit_map[b3]);
	led_panel_write_byte(digit_map[b2]);
	led_panel_write_byte(digit_map[b1]);
	// Latch everything
	GPIO_write(GPIOB, 4, 1);
	asm ( "nop" ); //~12 ns
	asm ( "nop" ); //~12 ns
	asm ( "nop" ); //~12 ns
	asm ( "nop" ); //~12 ns
	GPIO_write(GPIOB, 4, 0);
	// Enable outputs
	GPIO_write(GPIOB, 5, 0);
	GPIO_write(GPIOB, 3, 0);
	GPIO_write(GPIOA, 10, 0);
}

void led_panel_write_int(int v)
{
	int c, d, u;
	c = v / 100;
	d = (v % 100) / 10;
	u = v % 10;
	led_panel_write(c,d,u);
}

int main(void)
{
	uint8_t c = 0;
	led_panel_init();
	for (;;) {
		led_panel_write_int(c);
		delay_ms(500);
		c++;
	}
	return 0;
}
