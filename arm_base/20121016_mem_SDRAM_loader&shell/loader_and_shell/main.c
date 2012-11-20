#include "uart.h"
#include "stdio.h"
#include "print_SFR.h"
#include "gpio.h"
#include "nand.h"
#include "loader.h"
#include "shell.h"

int shell_enable(void)
{
	int flags = 0; 
	int i, j;
	char ch;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 0xfffff; j++) {
			if (!(GPH2DAT & 0X1)) {
				for (i = 0; i < 0XFFFF; i++)
					;
				if (!(GPH2DAT & 0X1))
					flags = 1;
			}
			if (UTRSTAT0 & 0x1) {
				flags = 1;
			}
		}
	while (UTRSTAT0 & 0x1) {
		ch = URXH0 & 0XFF;
	}
	return flags;
}

void loader_shell_init(void)
{
	key1_init();
	uart_init();
	nand_init();
}
void c_entry(void)
{
	loader_shell_init();
	my_printf("	   Please press K1 or keypad of other throuth the UART0\n");
	my_printf("to in the shell of bootloader\n");

	if (shell_enable()) {
		shell();
	} else {
		loader();
	}
}
