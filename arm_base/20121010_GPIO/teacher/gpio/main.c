#include "gpio.h"
int c_entry(void)
{
/*
	int i = 0;
	led_init();
	while(1)
	{
		led_on(i%4);
		delay(1);
		led_off(i%4);
		delay(1);
		i++;
	}
*/

	k1_init();
	buzzer_init();
	while(1)
	{
		if (k1_is_down())
		{
			buzzer_on();
			delay(1);
			buzzer_off();
		}
		else
			continue;
	}










	
}