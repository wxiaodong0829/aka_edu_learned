#include "uart.h"

void uart_init(void)
{
	/*
		1, GPA0_0: RXD0     GPA0_1: TXD0
		2, 8 N 1
		3, polling
		4, 115200
	*/
	GPA0CON &= 0XFFFFFF00;
	GPA0CON |= 0X22;
	
	ULCON0 &= 0XFFFFFF80;
	ULCON0 |= 0X3;
	
	UCON0 &= 0XFFF00000;
	UCON0 |= 0X5;
	
	UBRDIV0 &= 0XFFFF0000;
	UBRDIV0 |= 0X22;
	UDIVSLOT0 &= 0XFFFF0000;
	UDIVSLOT0 |= 0XDDDD;
}
int uart_getchar(void)
{
	//UTRSTAT0   R
	int ch;
	while (!(UTRSTAT0 & 0x1)) 
		;
	ch = URXH0 & 0XFF;
	return ch;
	
	//return ch;
}
void uart_putchar(int ch)
{
	//UTRSTAT0 T
	while (!(UTRSTAT0 & 0X2))
		;

	//UTXH0 &= (ch & 0XFF);
	UTXH0 = (ch & 0XFF);
	
}