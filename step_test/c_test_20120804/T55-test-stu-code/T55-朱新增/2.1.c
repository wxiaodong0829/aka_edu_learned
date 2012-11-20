#include<stdio.h>
#define N 10
int main()
{
	int num[]={5,4,6,8,9,7,2,6,10,12};

	int i,k,j,tmp;
	for(i=0;i<N-1;i++)
	{
		k=i;
		for(j=i+1;j<N;j++)
			if(num[j]>num[k])
				k=j;
		if(k!=i)
		{
			tmp=num[i];
			num[i]=num[k];
			num[k]=tmp;

		}	
	}
	for(i=0;i<N;i++)
		printf("%d\n",num[i]);


}
