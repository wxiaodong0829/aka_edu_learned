#include<stdio.h>
#define N 5	 
void zj_px(int arr[5][5],int N)
{
	int i,j,k,m,tmp;
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
			k=j;
		for(m=j+1;m<4;j++)
			if(arr[i][m]>arr[i][k])
				k=m;
		if(k!=i)
		{
			tmp=arr[i][j];
			arr[i][j]=arr[i][k];
			arr[i][k]=tmp;

		}

	}
}
int main()
{
	int i,j;
	int arr[5][5];
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)

			scanf("%d",&arr[i][j]);
	}
	zj_px(arr[5][5],5);
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)

			printf("%d\n",arr[i][j]);
	}
	return 0;
}
