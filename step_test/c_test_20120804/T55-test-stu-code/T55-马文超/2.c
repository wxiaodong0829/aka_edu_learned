#include <stdio.h>
#include <time.h>

#define N 10
int main(void)
{

    int i, j, k, tmp;
    int num[N];
    srand(time(NULL));
    for (i = 0; i < N; i++)
	num[i] = rand() % 100;
    printf("before sort:\n");
    for (i = 0; i < N; i++)
	printf("%3d", num[i]);
    printf("\n");
#if 1
    for (i = 0; i < N; i++)
    {
	k = i;
	for (j = i + 1; j < N; j++)
	    if (num[j] < num[k])
		k = j;
	if (k != i)
	{
	    tmp = num[i];
	    num[i] = num[k];
	    num[k] = tmp;
	}
    }
    printf("after selectsort:\n");
    for (i = 0; i < 10; i++)
	printf("%3d", num[i]);
    printf("\n");
#endif
    for (i = 0; i < N - 1; i++)
    {
	for (j = N - 2; j >= i; j--)
	{
	    if (num[j+1] < num[j])
	    {
		tmp = num[j+1];
		num[j+1] = num[j];
		num[j] = tmp;
	    }
	}
    }

    printf("after bubblesort:\n");
    for (i = 0; i < 10; i++)
	printf("%3d", num[i]);
    printf("\n");
    return 0;
}
