#include<stdio.h>

#define N 100
char buf[N];
char a[N];
char b[N];

char *dostr(char * s)
{
	int i,j=0,t=0;
	for(i=0;s[i];i++)
	{
		if(isalpha(s[i]))
			a[j++]=s[i];
		else
			b[t++]=s[i];
			
	}
	b[t]='\0';
	t=0;
	while(b[t++])
		a[j++]=b[t++];
	a[j]='\0';
	return a;
}

int main(void)
{
	char *p;
	scanf("%s",buf);
	p=dostr(buf);
	printf("%s\n",p);	
	return 0;
}
