#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

char *vstrcat(const char *first, ...)
{
	size_t len;
	char *retbuf;
	va_list argp;
	char *p;

	if(first == NULL)
		return NULL;

	len = strlen(first);

	va_start(argp, first);
	while((p = va_arg(argp, char *)) != NULL)
		len += strlen(p);
	va_end(argp);

	retbuf = malloc(len + 1); /* + 1 包含终止符 '\0' */
	if(retbuf == NULL)
		return NULL;

	(void)strcpy(retbuf, first);

	va_start(argp, first);
	while((p = va_arg(argp, char *)) != NULL)
		(void)strcat(retbuf, p);

	va_end(argp); 
	return retbuf;
}

int main(void)
{
	char *str = vstrcat("Hello,", "world!");
	//char *str = vstrcat("Hello,", "world!", (char *)NULL);

	printf("%s\n", str);

	return 0;

}
