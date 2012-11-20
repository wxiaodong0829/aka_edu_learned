#include "uart.h"
#include "lib.h"
#include "nand.h"

int c_entry(void)
{
	char id[5];
	char buf[2048];
	int i;
	int addr;
	int nand_addr;
	int sdram_addr;
	
	uart_init();
	nand_init();
/*	nand_read_id(id);
		
	for (i = 0; i < 5; i++)
		putchar_hex(id[i]);
	puts("\n");
*/
	nand_addr = 0xfffc000;//0x1000000;//页对齐
	sdram_addr = 0x23000000;
	nand_read(nand_addr, (char *)sdram_addr, 0x1000);
//	myprintf("%x", *((unsigned int*)sdram_addr));

	((void (*)(void))sdram_addr)();

	return 0;
}
