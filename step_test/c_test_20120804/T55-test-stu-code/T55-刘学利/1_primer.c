#include <stdio.h>

void primer(int n)
{
	int i, j;
	printf("1, 2, ");
	for(i = 3; i < n; i++)
	{
		for(j = 2; j*j < i; j++)
		  if(i%j == 0)	break;
		if(j*j > i)
		  printf("%d, ", i);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	int n;
	scanf("%d", &n);
	primer(n);
	return 0;
}
