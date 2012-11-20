#include <stdio.h>
#include <string.h>

#define N 10

void swap(char *p, int i, int j)
{
	int tmp;
	tmp = p[i];
	p[i] = p[j];
	p[j] = tmp;
}

void reverse(char *p)
{
	int i = 0, j = strlen(p)-1;
	if(i >= j)
	  return ;
	swap(p, i, j);
	while(++i < --j)
	  swap(p, i, j);
}

char *myitoa(unsigned n, char *p)
{
	int i = 0, sign;
	if((sign = n) < 0)
	  n = -n;
	do
	{
		p[i++] = n%10 +'0';
	}while( (n /= 10) > 0);
	if(sign < 0)
	  p[i++]= '-';
	p[i] = '\0';
	reverse(p);

	return p;
}

int main(int argc, char *argv[])
{
	int a = 123;
	int b = -123;
	char s[N];
	strcpy(s,  myitoa(a, s));
	printf("%s\n", s);

	strcpy(s,  myitoa(b, s));
	printf("%s\n", s);

	return 0;
}
