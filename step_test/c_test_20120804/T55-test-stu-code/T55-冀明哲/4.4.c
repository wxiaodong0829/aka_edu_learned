#include<stdio.h>
#include<string.h>
#define N 10
int main()
{
	char a[N]="cdefg";
	int i, max=0;
	char tmp;

	for(i=1; i<N; i++)
		if(a[i]>a[max])
			max=i;
			
	tmp=a[max];
	for(i=max; i>0; i--)
		a[i]=a[i-1];

	a[0]=tmp;

	printf("%s\n", a);	
			
	return 0;
}
