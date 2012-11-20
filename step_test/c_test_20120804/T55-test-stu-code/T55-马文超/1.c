#include <stdio.h>

int main(void)
{
    int i, j, n;

    printf("put a number:");
    scanf("%d", &n);
    if (n < 2)
    {	printf("error\n");}
    else
	for (i = 3; i <= n; i++)
	{for (j = 2; j * j <= i; j++)
	    {	if ( i % j == 0 )
		 break;
	    }
	    if (j * j > i)
		printf ("%3d", i);
	}
    printf("  2\n");
    return 0;
}
