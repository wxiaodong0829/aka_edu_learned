#include <stdio.h>
#define N 100
int main()
{
    int i, j, p=1, flag;
    printf("   2");
    for (i=3; i<=N; i+=2) {
        flag = 1;
        for (j=2; j*j<=i; j++)
            if (i%j==0) { flag = 0; continue; }
        if (flag==1)
            printf("%4d%s", i, (++p)%10==0?"\n":"");
    }
    printf("\n");
    return 0;
}
//./a.out | factor | less