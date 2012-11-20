#include <stdio.h>
void prime(int n)
{
	int i, j;
	if (n<2) {
		printf("no prime!\n");
		return;
	}
	printf("2\n");
	for (i=3; i<=n; i+=2) {
		for (j=2; j*j<i; j++)
			if (i%j == 0)
				break;
		if (j*j > i)
			printf("%d\n", i);
	}
}
int main()
{
	int n;
	scanf("%d", &n);
	prime(n);
	return 0;
}
