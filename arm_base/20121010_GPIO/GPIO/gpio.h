#ifndef __GPIO__H__
#define __GPIO__H__

void delay(int sec);

/*-----------------------  led  --------------*/
#define GPJ2CON *(volatile unsigned int *)0XE0200280
#define GPJ2DAT *(volatile unsigned int *)0XE0200284


void led_init(void);

void led_on(int num);
void led_off(int num);

void led_all_on(void);
void led_all_off(void);

/*-----------------------  buzzer  --------------*/
#define GPD0CON *(volatile unsigned int *)0XE02000A0
#define GPD0DAT *(volatile unsigned int *)0XE02000A4

void buzzer_init(void);

void buzzer_on(void);
void buzzer_off(void);

/*-----------------------  key  --------------*/
#define GPH2CON *(volatile unsigned int *)0XE0200C40
#define GPH2DAT *(volatile unsigned int *)0XE0200C44

void key1_init(void);

int key1_is_down(void);



#endif