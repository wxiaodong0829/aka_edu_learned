#include <stdio.h>
#include <string.h>
#define N 16
void reverse(char s[])
{
        int i, j, tmp;
	for (i=0, j=strlen(s)-1; i<j; i++, j--)
		tmp = s[i], s[i] = s[j], s[j] = tmp;
}
char * itoa(unsigned n, char *s)
{
        int i=0, sign;
	if ((sign=n) < 0) n = -n;
	    do {
		    *(s+i) = n % 10 + '0';
		    i++;
		} while ((n/=10) > 0);
	if (sign < 0) *(s+i) = '-';
	*(s+i) = '\0';
        reverse(s);
	return s;
}
int main()
{
	char s[N];
	unsigned num = 1234567;
	printf("%s\n", itoa(num, s));
	return 0;
}
