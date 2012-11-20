/* led1~led4 */
#define GPJ2CON	 *((volatile unsigned int *)0xe0200280)
#define GPJ2DAT  *((volatile unsigned int *)0xe0200284)
/* beep */
#define GPD0CON	 *((volatile unsigned int *)0xe02000a0)
#define GPD0DAT  *((volatile unsigned int *)0xe02000a4)
/* button */
#define GPH2CON	 *((volatile unsigned int *)0xe0200c40)
#define GPH2DAT  *((volatile unsigned int *)0xe0200c44)
//extern int c_entry(void);
void beep_init(void)
{
	GPD0CON = 0X1;
	GPD0DAT = 0;
}
void beep_on(void)
{
	GPD0DAT |= 0x1;
}
void beep_off(void)
{
	GPD0DAT &= ~0x1;
}

void button_init(void)
{
	GPH2CON = 0X0;
	GPH2DAT = 0X0;
}
int button_is_down(void)
{
	if (GPH2DAT & 0X1)
		return 0;
	else
		return 1;
}

void led_init(void)
{
	GPJ2CON = 0x1111;
	GPJ2DAT = 0xF;
}

void led_on(int num)
{
	GPJ2DAT &= ~(1<<num);
}

void led_off(int num)
{
	GPJ2DAT |= (1<<num);
}
void delay(int sec)
{
	int i, j;
	for (i = 0; i < sec; i++)
		for (j = 0; j < 0x40000; j++)
			;
}
#if 1
int c_entry(void)
{
	int i = 0;
	led_init();
	while(1) {
		led_on(i%4);
		delay(1);
		led_off(i%4);
		delay(1);
		i++;
	}
	/*
	button_init();
	beep_init();
	while(1) {
		if (button_is_down())
			beep_on();
		else
			beep_off();
	}
	*/
	return 0;
}
#endif
