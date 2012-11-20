#include<stdio.h>
#include<time.h>
#define N 5

void xsort(int *s, int n)
{
	int i, j, k, tmp;
	for(i=0; i<n; i++)
	{ 
		k=i;
		for(j=i+1; j<n; j++)
			if(*(s+k)>*(s+j))
				k=j;

		if(k!=i)
		{
			tmp=*(s+k);
			*(s+k)=*(s+i);
			*(s+i)=tmp;
		}
	}

}
int main()
{
	int arr[5][5];
	int i, j;

	srand(time(NULL));

	for(i=0; i<N; i++)
	for(j=0; j<N; j++)
	arr[i][j]=rand()%10;

	for(i=0; i<N; i++)
	for(j=0; j<N; j++)
		{
			printf("%d ",arr[i][j]);
			if(j==4)
				printf("\n");
		}
		printf("\n");
		
	xsort(arr[1], 5);
	for(i=0; i<N; i++)
		printf("%d ",arr[1][i]);
		printf("\n");
		printf("\n");

	xsort((int *)arr, 25);
	for(i=0; i<N; i++)
	for(j=0; j<N; j++)
		{
			printf("%d ",arr[i][j]);
			if(j==4)
				printf("\n");
		}

}
