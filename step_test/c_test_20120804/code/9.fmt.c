/*************************************************************************
    > File Name: 9.fmt.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月04日 星期六 17时25分23秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

char *vstrcat(const char *first, ...)
{
	char *ret = NULL;
	char *tmp = NULL;
	va_list ap;

	int i;
	int len = 0;
	len = strlen(first);
	int num;

	va_start(ap, first);
	for (num = 0; *ap; num++) {
		tmp = va_arg(ap, char *);
		len += strlen((tmp));
	}
	ret = malloc(len+2);
	ret[0] = '\0';
	strcat(ret, first);
	va_start(ap, first);
	for (i = 0; *ap; i++) {
		tmp = va_arg(ap, char *);
		strcat(ret, tmp);
	}
	return ret;
}
int main(void)
{
	char *p = NULL;
	char a[] = "adfs";
	char b[] = "1324";
	p = vstrcat(a, b, NULL);
	printf("%s\n", p);
	free(p);
	
	return 0;
}
