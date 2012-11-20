#ifndef __GPIO_H_
#define __GPIO_H_
int led_init(void);
int led_on(int num);
int led_off(int num);
void beep_init(void);
void beep_on(void);
void beep_off(void);
void delay(int sec);
#endif