#include <stdio.h>

int main()
{
	int n, f, i, j, num = 1;
	scanf("%d", &n);
	for(i = 2; i <= n; i++)
	{
		f = 1;
		for(j = 2; j*j <= i; j++)
			if(i % j == 0)
			{
				f = 0;
				break;
			}
		if(f == 1)
		{
			printf(" %d", i);
			if(num++ %10 == 0)
				printf("\n");
		}
	}	
	printf("\n");

	return 0;
}

