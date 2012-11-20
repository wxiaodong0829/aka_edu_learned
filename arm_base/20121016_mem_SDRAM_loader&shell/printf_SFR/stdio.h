#ifndef __STDIO__H__
#define __STDIO__H__

#include "uart.h"

int my_getchar(void);
void my_putchar(int ch);

char * my_gets(char * s);  //当无退格时，用此更快
char * my_gets_cont_back(char * s); //当有退格时，用此更快

int my_puts(const char * s);

/*---------------------    printf    ------------------------*/
typedef char *va_list;
/* macros function */
#define va_arg(ap, T) \
	(*(T *)(((ap) += _Bnd(T, 3U)) - _Bnd(T, 3U)))
#define va_end(ap) (void)0
#define va_start(ap, A)\
	(void)((ap) = (char *)&A + _Bnd(A, 3U))
#define _Bnd(X, bnd) ((sizeof(X) + (bnd)) & (~(bnd))) // 4瀛楄妭瀵归綈 3U 琛ㄦ棤绗﹀彿鏁存暟

#define ITOA(n) "0123456789"[n]
#define ITOX(n) "0123456789ABCDEF"[n]

int my_printf(const char *fmt, ...);

#endif