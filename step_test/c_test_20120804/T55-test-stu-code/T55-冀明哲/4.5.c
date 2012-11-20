#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define N 100

char b[N];
char *fun(char *s)
{
	int i=0;
	char *tmp;
	tmp=s;
	while(*s!='\0')
	{
		if(isalpha(*s))
			b[i++]=*(s);
			s++;
	}
	while(*tmp!='\0')
	{
		if(isdigit(*tmp))
			b[i++]=*(tmp);
			tmp++;
	}
	b[i]='\0';
	return b;
	
}
int main()
{
	char a[N]="678abc90";
	char *s;

	s=fun(a);
	printf("%s\n", s);

	return 0;

}
