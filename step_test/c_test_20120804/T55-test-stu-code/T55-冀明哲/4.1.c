#include<stdio.h>

int main()
{
	int i, j, n, flag;

	scanf("%d",&n);
	printf("2\n");
	for (i=3; i<=n; i+=2) {
		flag = 1;
		for (j=2; j*j<=i; j++)
			if (i%j==0) { flag = 0; continue; }
		if (flag==1)
			printf("%d\n", i);
	}
	printf("\n");
	return 0;
}
