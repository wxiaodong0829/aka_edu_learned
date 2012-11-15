/*************************************************************************
    > File Name: printf.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月03日 星期五 16时24分00秒
 ************************************************************************/

#include <stdio.h>

#ifndef _STDARG
#define _STDARG
/*type definitions */
typedef char *va_list;
/* macros */
#define va_arg(ap, T) \
	(*(T *)(((ap) += _Bnd(T, 3U)) - _Bnd(T, 3U)))
#define va_end(ap) (void)0
#define va_start(ap, A)\
	(void)((ap) = (char *)&A + _Bnd(A, 3U))
#define _Bnd(X, bnd) ((sizeof(X) + (bnd)) & (~(bnd))) // 4字节对齐 3U 表无符号整数
#endif
#include <stdio.h>
//#include "stdarg_d.h"
#if 1
/*itoa.c*/
#include <stdlib.h>
#define ITOA(n) "0123456789"[n]
#define CHAR_BUF 30
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
char *itoa(unsigned n)
{
	int sign = 0;
	int i = -1;
	char *p = NULL;
	p = malloc(CHAR_BUF);

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
#endif

#define STR_FMT "a = %d, c = %c"
#define STR_FIR str_str.a
#define STR_SEC str_str.c
#define STR_FUNC (STR_FMT, STR_FIR, STR_SEC)

struct str {
	int a;
	char c;
}str_str = {1, 'c'};

typedef void(Fun_struct)(const char *fmt, ...); //just define this type
void stru(const char *fmt, ...)
{
	va_list ap;
	char c, c1;
	va_start(ap, fmt);// char * ap = fmt的下一个参数的地址。
	while (c = *fmt++) {
		if (c == '%') {
			switch (c1 = *fmt++) {
				case 'c': {
							  char ch = va_arg(ap, int);
							  putchar(ch);
							  break;
						  }
				case 's': {
							  char *p = va_arg(ap, char *);
							  fputs(p, stdout);
							  break;
						  }
				case 'd': {
							  int n = va_arg(ap, int);
							  char *pi = itoa(n);
							  fputs(pi, stdout);
							  free(pi);
							  break;
						  }
				case 'z': {
							  Fun_struct *fun = va_arg(ap, void *);
							  (*fun)STR_FUNC;
							  break;
						  }
				default:	  break;
			}
		} else putchar(c);
	}
	return;
}

int myprintf(const char *fmt, ...)
{
	va_list ap;
	char c, c1;
	va_start(ap, fmt);// char * ap = fmt的下一个参数的地址。
	while (c = *fmt++) {
		if (c == '%') {
			switch (c1 = *fmt++) {
				case 'c': {
							  char ch = va_arg(ap, int);
							  putchar(ch);
							  break;
						  }
				case 's': {
							  char *p = va_arg(ap, char *);
							  fputs(p, stdout);
							  break;
						  }
				case 'd': {
							  int n = va_arg(ap, int);
							  char *pi = itoa(n);
							  fputs(pi, stdout);
							  free(pi);
							  break;
						  }
				case 'z': {
							  Fun_struct *fun = va_arg(ap, void *);
							  (*fun)STR_FUNC;
							  break;
						  }
				default:	  break;
			}
		} else putchar(c);
	}
	return 0;
}

void init_str(void)
{
	str_str.a = 100;
	str_str.c = 'z';
}
int main(void)
{
	int m = 10;
	init_str();
//	printf("%d %c\n", str_str.a, str_str.c);
	myprintf("max = %c, %s, m = %d, strstr : %z\n", 'a', "adfasdg", m, stru);
//	printf("%s\n", itoa(0));
	
	return 0;
}
