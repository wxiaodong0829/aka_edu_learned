#include<stdio.h>
#include<string.h>
#define N 10

void reverse(char a[])
{
	int i, j;
	char tmp;
	for(i=0, j=strlen(a)-1; i<=j; i++,j-- )
	{
		tmp=a[i];	
		a[i]=a[j];
		a[j]=tmp;
	}
}
char *myitoa(int n, char *p)
{
	int i=0;
	int tmp=n;
	if(n<0)
		n=-n;
	do	
	{
		*(p+i)=n%10+'0';
		n/=10;
		i++;
	}while(n!=0);
	if(tmp<0)
	{
		*(p+i)='-';
		++i;
	}
	*(p+i)='\0';
	reverse(p);
	return p;
}
int main()
{
	char a[N], *s;	
	int n=-98745;

	s=myitoa(n, a);
	printf("%s", s);
	printf("\n");
}
