
#include "myxmodem.h"
#include "uart.h"
#include "stdio.h"

#define NULL 0

/* global error variable */
char *xmodem_errtxt = NULL;
int get_byte_err = 0;
U8 volatile receive_buffer[BLOCK_SIZE];
//unsigned download_addr = 0x8000;
/* prototypes of helper functions */
int get_record(void);

enum
{
	SAC_SEND_NAK = 0,
	SAC_SENT_NAK = 1,
	SAC_PAST_START_NAK = 2
};

static volatile int seen_a_char = SAC_SEND_NAK;

//static int one_nak = 0;
//static unsigned long xmodem_timeout = GET_BYTE_TIMEOUT;

char debugbuf[4096];

int db_idx = 0;

static void delay()
{
	int j;
	for (j = 0; j < 0x2f000000; j++)
		;
}

 int loadx(int argc, char *argv[])
{
	char ochr;
	int r = 0, rx_block_num = 0, error_count = 0;
	int foffset = 0;
	int i;
	unsigned int download_addr;
	char nak = NAK;

	xmodem_errtxt = NULL;
	seen_a_char = 0;
	
		
	
//	if(argc > 1) download_addr = atox(argv[1]);
//	else download_addr = 0x22000000;
	download_addr = 0x22000000;
#if 0
	uart0_putchar('9');	
	delay();
	uart0_putchar('8');
	delay();
	uart0_putchar('7');
	delay();
	uart0_putchar('6');
	delay();
	uart0_putchar('5');	
	delay();
	uart0_putchar('4');
	delay();
	uart0_putchar('3');
	delay();
	uart0_putchar('2');
	delay();
	uart0_putchar('1');
	delay();
	uart0_putchar('0');
#endif	
	//uart_putchar(uart0_BASE, nak);
	//uart0_putchar(nak);
	uart_putchar(nak);
	
	rx_block_num = 1;

	/* times to retry */
	error_count = RETRIES;

	do {
		/* when local block number equals to the block number in the packet,
			store the data into the memory which download_addr points*/
		if ((r = get_record()) == (rx_block_num & 255)) {
			error_count = RETRIES;
			for (i = 0; i <BLOCK_SIZE; i++)
				*(U8 *)(download_addr+foffset+i) = receive_buffer[i];
			xmodem_errtxt = "RX PACKET";
			rx_block_num++;
			ochr = ACK;
			foffset += BLOCK_SIZE;
		} else {
			switch (r) {
			case -1: /* TIMEOUT */
				xmodem_errtxt = "TIMEOUT";
				ochr = NAK;
				break;
			case -2: /* Bad block */
				xmodem_errtxt = "BAD BLOCK#";
				/* eat teh rest of the block */
#if 0
				get_byte_err = 0;
				while (get_byte_err != -1) get_byte();
#endif
				ochr = NAK;
				break;
			case -3: /* Bad checksum */
				xmodem_errtxt = "BAD CHKSUM";
				ochr = NAK;
				break;
			case -4: /* End of file */
				xmodem_errtxt = "DONE";
				ochr = ACK;
				break;
			case -5: /* Cancel */
				xmodem_errtxt = "ABORTED";
				ochr = ACK;
				break;
			default: /* Block out of sequence */
				xmodem_errtxt = "WRONG BLK";
				ochr = NAK;
			}
			error_count--;
		}

		uart_putchar(ochr);
	} while ((r > -3) && error_count);

	if ((!error_count) || (r != -4)) {
		foffset = 0;	/* indicate failure to caller */
	}
    my_printf( "Loaded file at address 0x%x, size = %d \r\n",(int)download_addr, foffset);

	return foffset;
}

/*
 * Read a record in the XMODEM protocol, return the block number
 * (0-255) if successful, or one of the following return codes:
 * 	-1 = Bad byte
 * 	-2 = Bad block number
 * 	-3 = Bad block checksum
 * 	-4 = End of file
 * 	-5 = Canceled by remote
 */
int get_record(void)
{
	char c; 
	int block_num = 0;
	int i;

	U32 check_sum;

	/* clear the buffer */
	for (i = 0; i < BLOCK_SIZE; i++)
		receive_buffer[i] = 0x00;

	check_sum = 0;

	/* initialize i to -2,when begin to transfer,the first byte
	   will be store into blcok_num,and after plused one,the next
	   byte will be treated as a negated section */
	i = -2;
	//uart_getchar( uart0_BASE, &c);
	c = uart_getchar();

	switch (c) 
	{
		case SOH:	/* Receive packet */
			for (;;) 
			{
				//uart_getchar( uart0_BASE, &c);
				c = uart_getchar();

				switch (i) 
				{
					case -2: 
						block_num = c;
						break;
				
					case -1:
#if 0
#ifdef CHECK_NEGATED_SECTNUM
				if (c != (-block_num -1))
					return -2;
#endif
#endif
						break;
					case BLOCK_SIZE:
					/* check if reveived data is correct,
				   	when correct,block num is returned,
				  	 else -3 is returned */
						if ((check_sum & 0xff) != c)
							return -3;
						else
							return block_num;
						break;
					
					default:
					/* save data to buffer,and accumulate to check_sum */
						receive_buffer[i] = c;
						check_sum += c;
				}
				i++;
			}
	case EOT:	/* end of file encountered */
		return -4;
	case CAN:	/* cancel protocol */
		return -5;
	default:
		return -5;
	}
}


