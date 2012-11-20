#ifndef __UART__H__
#define __UART__H__

#define GPA0CON *(volatile unsigned int *)0XE0200000	// GPA0  设置为功能管脚

#define ULCON0  *(volatile unsigned int *)0xE2900000 // 8 N 1

#define UCON0   *(volatile unsigned int *)0xE2900004 // polling 轮询

#define UTRSTAT0 *(volatile unsigned int *)0xE2900010 // 收发状态

#define UTXH0 	*(volatile unsigned int *)0xE2900020 // 发
#define URXH0	*(volatile unsigned int *)0xE2900024 // 收

#define UBRDIV0 *(volatile unsigned int *)0xE2900028   // 115200 bps
#define UDIVSLOT0 *(volatile unsigned int *)0xE290002C // 115200 bps

void uart_init(void);

int uart_getchar(void);

void uart_putchar(int ch);


#endif