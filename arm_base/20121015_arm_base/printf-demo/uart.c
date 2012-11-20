#define GPA0CON  	(*(volatile unsigned int *)0xE0200000) 
#define GPA1CON  	(*(volatile unsigned int *)0xE0200020) 

#define ULCON0  	(*(volatile unsigned int *)0xE2900000) 
#define UCON0  		(*(volatile unsigned int *)0xE2900004) 
#define UTRSTAT0  	(*(volatile unsigned int *)0xE2900010)
#define UTXH0  		(*(volatile unsigned char *)0xE2900020) 
#define URXH0  		(*(volatile unsigned char *)0xE2900024) 
#define UBRDIV0 	(*(volatile unsigned int *)0xE2900028) 
#define UDIVSLOT0  	(*(volatile unsigned int *)0xE290002C) 

#define ULCON3  	(*(volatile unsigned int *)0xE2900C00) 
#define UCON3  		(*(volatile unsigned int *)0xE2900C04) 
#define UTRSTAT3  	(*(volatile unsigned int *)0xE2900C10)
#define UTXH3  		(*(volatile unsigned char *)0xE2900C20) 
#define URXH3  		(*(volatile unsigned char *)0xE2900C24) 
#define UBRDIV3 	(*(volatile unsigned int *)0xE2900C28) 
#define UDIVSLOT3  	(*(volatile unsigned int *)0xE2900C2C) 

#undef UART0
#undef UART3

#define UART0	1
//#define UART3	1

#ifdef UART0
void uart_init(void)
{
	GPA0CON = 0X2222;
	// 8 bit N 1
	ULCON0 = 0x3;
	// T&R 01 = Interrupt request or polling mode 
	UCON0 = 0X5;
	UBRDIV0 = 0x23;
//	UDIVSLOT0 = 0X0808;
	//12 1
	UDIVSLOT0 = 0XDDDD; 
	// 66Mhz / (115200*16) - 1 = 0x23
	// 66Mhz / (19200*16) - 1 = 0xD5
	//UBRDIV0 = 0xD5;
	return;
}

char uart_getchar(void)
{
	char c;
	// polling receive status: if buffer is full
	//while ((UTRSTAT0 & (1<<0)) == 0)
	while (!(UTRSTAT0 & (1<<0)))
		;
	
	c = URXH0;
		
	return c;
}

void uart_putchar(char c)
{
	// polling transmit status: if buffer is empty
	//while ((UTRSTAT0 & (1<<2)) == 0)
	while (!(UTRSTAT0 & (1<<2)))
		;
	
	UTXH0 = c;
	
	return;
}
#endif

#ifdef UART3
void uart_init(void)
{
	GPA1CON = 0x2222;
	// 8 bit N 1
	ULCON3 = 0x3;
	// T&R 01 = Interrupt request or polling mode 
	UCON3 = 0X5;
	UBRDIV3 = 0x23;
	UDIVSLOT3 = 0X0808;
	// 66Mhz / (115200*16) - 1 = 0x23
	// 66Mhz / (19200*16) - 1 = 0xD5
	//UBRDIV0 = 0xD5;
	return;
}

char uart_getchar(void)
{
	char c;
	// polling receive status: if buffer is full
	//while ((UTRSTAT0 & (1<<0)) == 0)
	while (!(UTRSTAT3 & (1<<0)))
		;
	
	c = URXH3;
		
	return c;
}

void uart_putchar(char c)
{
	// polling transmit status: if buffer is empty
	//while ((UTRSTAT0 & (1<<2)) == 0)
	while (!(UTRSTAT3 & (1<<2)))
		;
	
	UTXH3 = c;
	
	return;
}
#endif
