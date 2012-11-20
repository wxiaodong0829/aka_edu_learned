#include "uart.h"
#include "stdio.h"
#include "print_SFR.h"

void c_entry(void)
{
	my_printf("DMC0\n");
	print_SFR(0xf0000000,0xf00000dc);
}
