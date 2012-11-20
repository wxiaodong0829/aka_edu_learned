#include <stdio.h>

void primes(int n)
{
	int i, j;
	printf("2\n");
	for(i=3; i<=n; i+=2)
	{
		for(j=2; j*j<i; j++)
			if(i%j == 0)
				break;
		if(j*j > i)
			printf("%d\n", i);
    }
}

int main(int argc, char *argv[])
{
    int n;

	scanf("%d", &n);

	primes(n);

	return 0;
}
