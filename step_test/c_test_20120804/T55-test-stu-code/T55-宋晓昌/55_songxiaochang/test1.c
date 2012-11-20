#include<stdio.h>
int main(void)
{
	int i,j,k;
	int m;
	scanf("%d",&m);
	for(i=2;i<m;i++)
	{
		for(k=2;k<=i;k++)
		{
			if(i%k==0)
			break;
		}
		if(k<i)
		{
			//printf("this is not sushu");
		}
		else
		{
			printf("this is sushu:%d\n",i);
		}
	}
	return 0;
}
