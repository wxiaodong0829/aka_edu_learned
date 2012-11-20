#include "uart.h"
#include "stdio.h"

void c_entry(void)
{
//	uart_putchar(ch);
#if 0
	int ch;

	while (1) {
		ch = my_getchar();
		my_putchar(ch);
	}
#endif

	char s[100];
	int ch;
	
	my_puts("abcd\b\n");
	
	my_printf("hello word! %d %s %x  %c", 10, "dong", 0x12345678, '\n');
	my_printf("%x %x\n", 0xffffffff, 0x00000000);
	
	while (1) {
		my_gets(s);
		my_puts(s);
	}



}