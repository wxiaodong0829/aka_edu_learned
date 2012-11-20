
#include "lib.h"
//#include "uart.h"
#if 0

void putchar_hex(char c)
{
	char * hex = "0123456789ABCDEF";
	
	uart_putchar(hex[(c>>4) & 0x0F]);
	uart_putchar(hex[(c>>0) & 0x0F]);

	return;
}

void putchar(char c)
{
	// '\n' -> '\r' + '\n'
	if (c == '\n')
		uart_putchar('\r');
		
	uart_putchar(c);
}

void putint_hex(int n)
{
	putchar_hex((n>>24) & 0xFF);
	putchar_hex((n>>16) & 0xFF);
	putchar_hex((n>>8) & 0xFF);
	putchar_hex((n>>0) & 0xFF);
	uart_putchar(' ');
	
	return;
}

int puts(const char * s)
{
	const char * p = s;
	
	while (*p)
		putchar(*p++);
		
	return (p - s);
}

int strlen(const char * s)
{
	const char * p = s;
	
	while (*p)
		p++;
		
	return (p - s);
}

char * reverse(char * s)
{
	static int counter = 1;
	static char * p;	
	char save;
	
	if (counter == 1)
		p = s;
	
	counter++;	
	
	if (*s == '\0')
	{
		counter = 1;
		return s;
	}
	
	save = s[0];	
	reverse(s+1);	
	*p++ = save;	
	
	return s;
}

char * reverse_r(char * s)
{
	int len = strlen(s);
	char c1 = s[0];
	char c2 = s[len-1];
	
	if (*s == '\0')
		return s;
		
	s[len-1] = '\0';
	
	reverse(s+1);
	
	s[0] = c2;
	s[len-1] = c1;
	
	return s;
}

char * reverse0(char * s)
{
	int len = strlen(s);
	int i;
	
	for (i = 0; i < len / 2; i++)
	{
		char tmp;
		
		tmp = s[i];
		s[i] = s[len-i-1];
		s[len-i-1] = tmp;
	}
	
	return s;
}

char * itoa(int n, char * s)
{	
	char * p = s;
	
	do
	{
		*p++ = n % 10 + '0';
		n = n / 10;		
	} while (n);
	
	*p = '\0';
	
	reverse(s);
	
	return s;
}
unsigned int my_square(int l, int n)
{
	unsigned int ret;
	int i;

	for (i = 0, ret = 1; i < n; i++)
		ret *= l;
	return ret;
}
unsigned int char_to_i(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	else if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
}
unsigned int my_atox(char *str)
{
	const char *s = str + 2;
	int len = strlen(s);
	unsigned int ret;
	int i;

	for (i = 0, ret = 0; i < len; i++) {
		ret += char_to_i(s[i]) * my_square(16, len - i - 1);
	}

	return ret;
}


#endif

unsigned int atox(char *p)
{
	int ret = 0;
	if (*(p + 1) == 'x') {//16进制 
		p += 2;
		while (*p) {
			if (*p >= '0' && *p <= '9') {
				ret = (ret * 16) + (*p - '0');
				p++;
			}else {
				ret = (ret * 16) + (*p - 'a' + 10);
				p++;
			}
		}
	} else {
		while (*p) {
			ret = (ret * 10) + (*p - '0');
			p++;
		}
	}

	return ret;
}
