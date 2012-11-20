#include<stdio.h>

#define N 100
char buf[N];

void maxchar(char *p)	 
{
	char c;
	int m=0,i=0;
	c=p[i];
	for(i=1;p[i];i++)
	{
		if(c<p[i])	
		{
			c=p[i];
			m=i;

		}		
	}
	while(m>0)
	{
	p[m]=p[m-1];
	m--;
	}
	p[0]=c;
}

int main(void)
{
	scanf("%s",buf);
	maxchar(buf);
	printf("%s\n",buf);
	
	return 0;
}
