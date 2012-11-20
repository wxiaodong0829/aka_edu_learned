#include "gpio.h"
void delay(int sec)
{
	int i, j;
	for (i = 0; i < sec; i++)
		for (j = 0; j < 0XFFFFFFF; j++)
			;
}
/*-----------------------  led  --------------*/
void led_init(void)
{
	GPJ2CON &= 0XFFFF0000;
	GPJ2CON |= 0X1111;

	GPJ2DAT |= 0XF;
}

void led_on(int num)
{
	GPJ2DAT &= ~(1 << num);
}
void led_off(int num)
{
	GPJ2DAT |=  (1 << num);
}

void led_all_on(void)
{
	GPJ2DAT &= ~(0XF);
}
void led_all_off(void)
{
	GPJ2DAT |=  (0XF);
}	

/*-----------------------  buzzer  --------------*/
void buzzer_init(void)
{
	GPD0CON &= 0XFFFFFFF0;
	GPD0CON |= 0X1;

	GPD0DAT &= ~(1);
}

void buzzer_on(void)
{
	GPD0DAT |= 0X1;
}
void buzzer_off(void)
{
	GPD0DAT &= ~(1);
}

/*-----------------------  key  --------------*/
void key1_init(void)
{
	GPH2CON &= 0XFFFFFFF0;
}

int key1_is_down(void)
{
	int i = 0;
	if (!(GPH2DAT & 0X1)) {
		for (i = 0; i < 0XFFFF; i++)
			;
		return !(GPH2DAT & 0X1);
	}
	return 0;
}



