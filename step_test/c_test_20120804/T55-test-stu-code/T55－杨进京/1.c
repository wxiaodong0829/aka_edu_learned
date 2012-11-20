#include <stdio.h>

void prime(int n)
{
    int i, j;
    printf("2 ");
    for (i = 3; i <= n; i += 2)
    {
        for (j = 2; j*j < i; j++)
            if (i % j == 0)
                break;
        if (j*j > i)
            printf("%d ", i);
    }
    printf("\n");
}

int main()
{
    int n;

    scanf("%d", &n);
    prime(n);

    return 0;
}
