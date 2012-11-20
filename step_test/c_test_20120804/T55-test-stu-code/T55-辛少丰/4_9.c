#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 512
typedef char * va_list;
#define va_start(ap, A) ap = &(A)
#define va_arg(ap, T) *(T *)(ap = (char *)ap + sizeof(T))
#define va_end(ap) ap(void *)0
char * vstrcat(const char *first, ...)
{
	char **ap;
	char *buf = malloc(M);
	va_start(ap, first);
	char **p = ap;
	int len=0;
	printf("%s\n", first);
	printf("%p\n", &first);
	printf("%p\n", ap);
	printf("%s\n", *ap);
	while (*p){
		//len = strlen(*p);
		strncpy(buf+len, *p, len);
		len += strlen(*p);
		p = va_arg(ap, char *);
		printf("%s\n", *p);
	}	
	*(buf+len)='\0';
	return buf;
}
int main()
{
	char *str=NULL;
	str = vstrcat("abc", "efr", "defg", NULL);
	printf("%s\n", str);
	return 0;
}
