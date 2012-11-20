#include <stdio.h>

int main(void)
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

	printf("Original string: %s\n", p);
	printf("Copied string: %s\n",dst_print);
	
	return 0;
}