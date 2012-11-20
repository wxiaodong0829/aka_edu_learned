#include <stdio.h>

int main(void)
{
    int i, j;
    int n;
    printf("Input src:");
    scanf("%d", &n);
    for (i = 1; i <= n; i++){
	for (j = 2; j < i; j++)
	    if (i % j == 0)
		break;
	if (j == i)
		printf("%d\n", i);
    }

    return 0;
}
