#include <stdio.h>
#include <string.h>
#define M 10

void reverse(char *p)
{
	int i, j = strlen(p) - 1;
	char tmp;
	for(i = 0, j; i < j; i++, j--)
	{
		tmp = p[i];
		p[i] = p[j];
		p[j] = tmp;
	}

}
char * myitoa(int n, char *p)
{
	int i = 0, sign;
	sign = n;
	if(n < 0) n = -n;
	do {
		p[i++] = n % 10 + '0';
	}while (n /= 10);
	if (sign < 0) p[i++] = '-';
	*(p + i) = '\0' ;
	return p;
}

int main()
{
	int n = -43452;
	char p[M];

	myitoa(n, p);
	reverse(p);

	printf("%s\n",p);

	return 0;
}
