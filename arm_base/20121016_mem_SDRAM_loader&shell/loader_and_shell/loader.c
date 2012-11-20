#include "loader.h"
void loader(void)
{
	char id[5];
	char buf[2048];
	int i;
	int addr;
	int nand_addr;
	int sdram_addr;
	
	my_printf("in loader...\n");
#if 0
	nand_addr = 0xfffc000;//0x1000000;//页对齐
	sdram_addr = 0x23000000;
	nand_read(nand_addr, (char *)sdram_addr, 0x1000);
//	myprintf("%x", *((unsigned int*)sdram_addr));

	((void (*)(void))sdram_addr)();

#endif

}
