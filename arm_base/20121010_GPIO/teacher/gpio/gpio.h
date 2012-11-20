#ifndef __GPIO_H_
#define __GPIO_H_
void led_init(void);
void led_on(int num);
void led_off(int num);
void delay(int sec);
void k1_init(void);
int k1_is_down(void);
void buzzer_init(void);
void buzzer_off(void);
void buzzer_on(void);
#endif