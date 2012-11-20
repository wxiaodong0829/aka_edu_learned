#include <stdio.h>
#include<string.h>
#define N 50

void swap(char s[])
{
	int l,r;
	char tmp;
	l =0,r =strlen(s) -1;
	while(l <= r)
	{
		tmp =s[l]; s[l] =s[r];s[r] =tmp;
		l++; r--;
	}
}
char *myitoa(int n, char *p)
{
	int sign,i =0;

	if((sign =n) < 0)
		n =-n;
	do
	{
		p[i++] =n%10 +'0';
	}while(n/=10);
	if(sign < 0)
		p[i++] ='-';
	p[i] ='\0';
	swap(p);

	return p;
}
int main ()
{
	int n;
	scanf("%d",&n);
	char *p,src[N];
	p =myitoa(n ,src);
	printf("%s\n",p);

	return 0;
}
