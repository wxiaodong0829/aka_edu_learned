#include "uart.h"
#include "stdio.h"

int my_getchar(void)
{
	int ch;
	ch = uart_getchar();
	return ch;
}
void my_putchar(int ch)
{
	if (ch == '\r') {
		uart_putchar(ch);
		uart_putchar('\n');
	} else if (ch == '\b') {
		uart_putchar(ch);
		uart_putchar(' ');
	} else if (ch == '\n') {
		uart_putchar(ch);
		uart_putchar('\r');
	}
	
	uart_putchar(ch);
}
char * my_gets(char * s)  //µ±ÎŞÍË¸ñÊ±£¬ÓÃ´Ë¸ü¿ì
{
	int i;
	for (i = 0; ; i++) {
		s[i] = my_getchar();
		my_putchar(s[i]);								
		if (s[i] == '\r') 
			break;
	}
	s[i] = '\0';
	return s;
}

char * my_gets_cont_back(char * s) //µ±ÓĞÍË¸ñÊ±£¬ÓÃ´Ë¸ü¿ì
{
	int i;
	for (i = 0; ; i++) {
		s[i] = my_getchar();
		my_putchar(s[i]);
		if (s[i] == '\b') { 			// Ìá¸ßĞ§ÂÊ£¬ÒòÎªIOÊÇ×îÕ¼Ê±¼äµÄ£¬
			i--;							
			continue;					// ÕâÑù¿É¼õÉÙ Ò»´Î'\b' Êä³ö
		} else if (s[i] == '\r') {
			break;
		}
	}
	s[i] = '\0';
	return s;
}
int my_puts(const char * s)
{
	int i;
	for (i = 0; s[i]; i++) {
		my_putchar(s[i]);
	}
	return 0;
}

/*--------------------------------------  printf  -------------*/
void reverse(char *buf, int l, int r)
{
	char tmp;
	while (l < r) {
		tmp = buf[l];
		buf[l] = buf[r];
		buf[r] = tmp;

		l++;
		r--;
	}
}
char *itox(unsigned n, char *p)
{
	int i = 0;
	int sign = sizeof(n);
	int a ,b, c, d;
	for (i = 0; i < sign*2; i++){
		a = 0xf0000000 >> (i * sign);
		b = n & a;
		c = (((sign * 2) - i - 1) * sign);
		d = (b >> c) & 0xf;
		p[i] = ITOX(d);
		//my_printf("a = %d,b = %d,c = %d,d = %d\r", a, b, c, d);
	} 
	p[i] = '\0';
	
	return p;
}
char *itoa(unsigned n, char *p)
{
	int sign = 0;
	int i = -1;

	if ((sign = n) < 0) {
		p[0] = '-';
		sign = -1;
		i = 0;
		n = -n;
	}

	do {
		p[++i] = ITOA(n%10);
	} while (n = n/10);
	p[++i] = '\0';

	if (sign == -1) {
		reverse(p, 1, i-1);
		return p;
	} 
	reverse(p, 0, i-1);

	return p;
}
int my_printf(const char *fmt, ...)
{
	va_list ap;
	char c, c1;
	va_start(ap, fmt);// char * ap = fmtçš„ä¸‹ä¸€ä¸ªå‚æ•°çš„åœ°å€ã€‚
	while (c = *fmt++) {
		if (c == '%') {
			switch (c1 = *fmt++) {
				case 'c': {
							  char ch = va_arg(ap, int);
							  my_putchar(ch);
							  break;
						  }
				case 's': {
							  char *p = va_arg(ap, char *);
							  my_puts(p);
							  break;
						  }
				case 'd': {
							  int n = va_arg(ap, int);
							  char pi[30];
							  itoa(n, pi);
							  my_puts(pi);
							  
							  break;
						  }
				case 'x': {
							  int x = va_arg(ap, int);
							  char px[20];
							  px[0] = '0';
							  px[1] = 'x';
							  itox(x, px + 2);
							  my_puts(px);
							  break;
						  }
				default:	  break;
			}
		} else my_putchar(c);
	}
	return 0;
}

/*--------------------------------------  printf  -------------*/