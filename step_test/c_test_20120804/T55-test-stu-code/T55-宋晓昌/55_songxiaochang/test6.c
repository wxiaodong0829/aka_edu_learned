
#include<stdio.h>
void myitoa(int n)
{
	char num[]={'0','1','2','3','4','5','6','7',
				'8','9'};
	int i=0;
	int j;
	int m;
	char tmp;
	char str[100];
	do
	{
		str[i]=num[n%10];
		i++;

	}while(n=n/10);
	str[i]='\0';
	for(--i,j=0;j<=i;i--,j++)

	{
		tmp=str[j];
		str[j]=str[i];
		str[i]=tmp;
	}
	printf("%s\n",str);	
}
int main(void)
{
	myitoa(123);
	return 0;
}


