#include <stdio.h>
#include <time.h>

#define N 5 

void swap(int *a, int *b) 
{ 
	int tmp; 
	tmp=*a, *a=*b, *b=tmp;
}

void arr_line_sort(int *s[])
{
    int i, j=0, k;

	for(i=0; i<N; i++)
		while(j++ < N-1)
			for(k=0; k<N-j; k++)
				if(s[i][k] > s[i][k+1])
					swap(&s[i][k], &s[i][k+1]);
}

void arr_sort(int *s[])
{
	int i, j, k;

}

void arr_c_sort(int *s[])
{
	int i, j, k;

}

int main(int argc, char *argv[])
{
	int arr[N][N], i, j;
	int **p = arr;

	srand(time(NULL));
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
		    arr[i][j] = rand()%500;

	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		    printf("%d   ", arr[i][j]);
	    printf("\n");
	}


    arr_line_sort();
//	arr_sort(*p);
//	arr_c_sort(arr);

	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		    printf("%d   ", arr[i][j]);
	    printf("\n");
	}
    printf("\n");
	
	return 0;
}
