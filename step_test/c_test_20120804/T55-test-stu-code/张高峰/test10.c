#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define N 20
char buf[N];
char num[10];
typedef float (*F)(float a,char c,float b);

float cal(float a,char c,float b)
{
	float s=0;
	switch(c)
	{
		case '+':
			s=a+b;	
			break;
		case '-':
			s=a-b;	
			break;
		case '*':
			s=a*b;	
			break;
		case '/':
			s=a/b;	
			break;

	}
	return s;
}
int main(void)
{
	char c;
	int i=0,j;
	float m,n,sum;
	while(1)
	{
		j=0;	
		scanf("%s",buf);
		char g=buf[0];
		if(g=='#')
			exit(0);
	for(i=0;buf[i];i++)
	{
		if(buf[i]>'0'&&buf[i]<'9')	
			num[j++]=buf[i];
		else
		{
			c=buf[i];
			m=atof(num);
			j=0;
		}

	}
	num[j]='\0';
	F f;
	f=cal;
	n=atof(num);
	sum=f(m,c,n);
	printf("the sum is:%f\n",sum);
	}

	return 0;

}
