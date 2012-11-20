#include<stdio.h>

iss(int i)
{
	int j;
	if(i<=1)
		return 0;
	if(i==2)
		return 1;
	for(j=2;j<i;j++)
	{
		if(i%j==0)
			return 0;
		else if(i!=j+1)
			continue;
		else
			return 1;
	}

}

int main(void)
{
	int n,i;
	scanf("%d",&n);	
	for(i=1;i<=n;i++)
		if(iss(i))
			printf("%d ",i);
	printf("\n");

	return 0;
}
