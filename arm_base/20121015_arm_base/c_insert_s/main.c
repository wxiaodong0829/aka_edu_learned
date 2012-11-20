#include "uart.h"
#include "stdio.h"

void c_entry(void)
{
	const char *src = "Hello world!";
	const char *p = src;
	char a[20];
	char *dst = a;
	char *dst_print = dst;
	int ch;
	
__asm
{
loop:
	LDRB ch, [src], #1
	STRB ch, [dst], #1
	CMP ch, #0
	BNE loop
}

	my_printf("Original string: %s\n", p);
	my_printf("Copied string: %s\n",dst_print);
	
}
