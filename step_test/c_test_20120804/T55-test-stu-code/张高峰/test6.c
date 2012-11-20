#include<stdio.h>

#define N 100

char *myitoa(int n,char *p)
{
	int i=0,j=0;
	char c;
	do{
		p[i++]=n%10+'0';
		
	}while((n /=10)>0);
	p[i]='\0';
	for(i--;j<i;j++,i--)
	{
		c=p[i];
		p[i]=p[j];
		p[j]=c;
	}
	return p;
}
int main(void)
{
	char buf[N],*p;
	int m;
	scanf("%d",&m);
	p=myitoa(m,buf);
	printf("%s\n",p);
	return 0;
}
