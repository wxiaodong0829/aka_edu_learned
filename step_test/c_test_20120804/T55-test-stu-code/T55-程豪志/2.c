#include <stdio.h>
#define N 10

int main(void)
{
    int num[10] = {3, 7, 10, 35, 23, 12, 55, 43, 6, 22};
    int i, j, k, tmp;
    printf("befor sort:");
    for (i = 0; i < N; i++)
	printf("%3d", num[i]);
    printf("\n");
#if 1
    for (i = 0; i < N-1; i++)
    {
	for (j = N - 2; j >= i; j--)
	    if(num[j + 1] < num[j])
	{
	    tmp = num[j + 1];
	    num[j + 1] = num[j];
	    num[j] = tmp;
	}
    }
    printf("after select sort:");
    for (i = 0; i < N; i++)
	printf("%3d", num[i]);
    printf("\n");
#endif

    for (i = 0; i < N - 1; i++)
    {
	k = i;
	for (j = i + 1; j < N; j++)
	    if(num[j] < num[k])
		k = j;
	if(k != i)
	{
	    tmp = num[i];
	    num[i] = num[k];
	    num[k] = tmp;
	}
    }
    printf("after bubble sort:");
    for (i = 0; i < N; i++)
	printf("%3d", num[i]);
    printf("\n");
}
