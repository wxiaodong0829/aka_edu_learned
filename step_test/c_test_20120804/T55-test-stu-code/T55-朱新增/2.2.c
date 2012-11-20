#include<stdio.h>
#define N 10 
int main()
{
	int num[10]={1,2,3,4,9,8,7,5,6,10};
	int i;
	int j;
	int tmp;
	for(i=0;i<10;i++)
	{
		for(j=9;j>0;j--)
			if(num[j]>num[j-1])
			{	
				tmp=num[j];
				num[j]=num[j-1];
				num[j-1]=tmp;
			}

	}

	for(i=0;i<10;i++)
		printf("%d\n",num[i]);	
	return 0;
}
