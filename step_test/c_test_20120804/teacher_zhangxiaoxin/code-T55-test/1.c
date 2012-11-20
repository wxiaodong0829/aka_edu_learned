#include <stdio.h>

int is_prime(int n)
{
	int i;

	for(i = 2; i < n; i++)
	{
		if((n % i) == 0)
			break;
	}
	if(n == i)
		return 1;
	else
		return 0;
}

int main(int argc, char *atgv[])
{
	int i, n;

	printf("Please input a num:");
	scanf("%d", &n);

	for(i = 0; i <= n; i++)
	{
		if(is_prime(i))
			printf("%d\n", i);
	}

	return 0;
}
