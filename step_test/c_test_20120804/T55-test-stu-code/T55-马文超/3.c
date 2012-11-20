#include <stdio.h>
#include <time.h>
int arr[5][5];
void selectsort(int *p, int r)
{
    int i, k,  j, tmp;
	for (i = 0; i <= r - 1; i++)
	{
	    k = i;
	    for (j = i + 1; j <= r - 1; j++)
		if (*(p+j) < *(p+k))
		    k = j;
	    if (k != i)
	    {
		tmp = *(p+i);
		*(p+i) = *(p+k);
		*(p+k) = tmp;
	    }
	}
}
int main(void)
{
    int i, j; 
    srand(time(NULL));
    for (i = 0; i < 5; i++)
    { 
        
	for (j = 0; j < 5; j++)
	    arr[i][j] = rand()%100;
    }	
    for (i = 0; i < 5; i++)
    {	for (j = 0; j < 5; j++)
	{
	    printf("%4d",arr[i][j] );
	if (j == 4)
	    printf ("\n");
	}
    }
    printf("one by one:\n");
    selectsort((int *)arr, 5);
    for (i = 0; i < 5; i++)
    {	
	for (j = 0; j < 5; j++)
	{
	    printf("%4d",arr[i][j] );
	    if (j == 4)
		printf ("\n");
	}
    }
    printf("all sort:\n");
    selectsort((int*)arr, 25);
    for (i = 0; i < 5; i++)
    {	for (j = 0; j < 5; j++)
	{
	    printf("%4d",arr[i][j] );
	    if (j == 4)
		printf ("\n");
	}
    }
    printf("\n");
    return 0;
}
