#include "gpio.h"

void led_1_to_4(void)
{
	int i, j;
	for (i = 0; i < 10; i++) {
		led_on(i%4);
		for (j = 0; j < 0XFFFFFF; j++)
			;
		led_off(i%4);
	}
}

void c_entry(void)
{
	int i;
	led_init();
	buzzer_init();
	key1_init();
	//led_1_to_4();
#if 1
	for (i = 0; ; i++) {
		if (key1_is_down()) {
			buzzer_on();
			led_1_to_4();
			led_all_on();
			delay(1);
			buzzer_off();
			led_all_off();
			
		} else {
			continue;
		}
	}
#endif

}