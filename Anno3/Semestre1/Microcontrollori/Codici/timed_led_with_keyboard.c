#include "stm32_unict_lib.h"

enum {
	OFF,
	ON
};

int state = OFF;
int last_pin_state;
int delay_count;

#define KEY_NONE  -1
#define KEY_X     0
#define KEY_Y     1
#define KEY_Z     2
#define KEY_T     3

typedef struct {
	int last_pin_state;
	GPIO_TypeDef * port;
	int pin;
} t_key;

t_key keys[4] =
	{ {0, GPIOB, 10},
	  {0, GPIOB, 4},
	  {0, GPIOB, 5},
	  {0, GPIOB, 6} };

void init_key(void)
{
	int i;
	for (i = 0; i< 4;i++) {
		GPIO_init(keys[i].port);
		GPIO_config_input(keys[i].port, keys[i].pin);
		keys[i].last_pin_state = GPIO_read(keys[i].port, keys[i].pin);
	}
}

int get_key(void)
{
	int i;
	int key_event = KEY_NONE;
	for (i = 0; i < 4;i++) {
		int pinval = GPIO_read(keys[i].port, keys[i].pin);
		if (keys[i].last_pin_state == 1 && pinval == 0) {
			key_event = i;
		}
		keys[i].last_pin_state = pinval;
	}
	return key_event;
}





void setup(void)
{
	DISPLAY_init();
	GPIO_init(GPIOB);
	GPIO_config_output(GPIOB, 0);
	init_key();
}

void loop(void)
{
	int key = get_key();
	if (key == KEY_X) {
		// pushbutton X pressed
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
	else if (key == KEY_Y && state == ON) {
		// spegni la luce
		state = OFF;
		GPIO_write(GPIOB, 0, 0);
	}

	switch(state) {
	case ON:
		delay_ms(10);
		++delay_count;
		if (delay_count == 1000) {
			state = OFF;
			GPIO_write(GPIOB, 0, 0);
		}
		int seconds = delay_count / 100;
		char s[5];
		sprintf(s,"%4d",seconds);
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
