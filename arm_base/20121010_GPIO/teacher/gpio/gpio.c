#define  GPJ2CON *((volatile unsigned int *)0XE0200280)
#define  GPJ2DAT *((volatile unsigned int *)0XE0200284)
#define  GPD0CON *((volatile unsigned int *)0XE02000A0)
#define  GPD0DAT *((volatile unsigned int *)0XE02000A4)
#define  GPH2CON *((volatile unsigned int *)0XE0200C40)
#define  GPH2DAT *((volatile unsigned int *)0XE0200C44)
void buzzer_init(void)
{
	GPD0CON &= 0XFFFFFFF0;
	GPD0CON |= 0X1;
	GPD0DAT &= ~1;
}
void buzzer_on(void)
{
	GPD0DAT |= 1;
}
void buzzer_off(void)
{
	GPD0DAT &= ~1;
}

void k1_init(void)
{
	GPH2CON &= 0XFFFFFFF0;
}
int k1_is_down(void)
{
	if (GPH2DAT & 1)
		return 0;
	else
		return 1;
}

void led_init(void)
{
	GPJ2CON &= 0XFFFF0000;
	GPJ2CON |= 0X1111;
	GPJ2DAT |= 0XF;
}
void led_on(int num)
{
	GPJ2DAT &= ~(1<<num);
}
void led_off(int num)
{
	GPJ2DAT |= (1<<num);
}
void led_all_on(void)
{
}
void led_all_off(void)
{
}

void delay(int sec)
{
	int i, j;
	for (i = 0; i < sec; i++)
		for (j = 0; j < 0XFFFFFF; j++)
			;
}













