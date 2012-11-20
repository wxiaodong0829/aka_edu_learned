
void nand_init(void);

void nand_read_id(char id[]);

void nand_read_page(int addr, char buf[]);

int nand_read(int nand_addr, char * sdram_addr, int size);