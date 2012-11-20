#include <stdio.h>

void prime(int n)
{
	int i,j;
	if(n==2)
		printf("the prime between 1 and 2 is 2.\n");
	printf("the prime between 1 and 2 is 2.\n");
	for(i=3;i<n;i+=2)
	{
		for(j=2;j*j<i;j++)
			if(i%j==0) break;
		if(j*j>i)
		printf("the prime between 2 and n is:%d\n",i);

	}
}
int main (void)
{

	int n;

	printf("Please enter a character:\n");
	scanf("%d",&n);

	prime(n);

}

