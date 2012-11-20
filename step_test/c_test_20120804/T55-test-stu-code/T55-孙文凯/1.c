#include <stdio.h>
void check(int n)
{
    int i, j, count;
    count = 0;
    if (n >= 2) {
        printf("%6d", 2);
        count++;
    }
    for (i=2; i<=n; i++)
        for (j=2; j<i; j++) {
            if (i % j ==0)
                break;
            if (j == i-1) {
                printf("%6d", i);
                if (++count % 10 == 0)
                    printf("\n");
            }
        }
    printf("\n");
}
int main(void)
{
    int n;
    scanf("%d", &n);
    check(n);
    return 0;
}
