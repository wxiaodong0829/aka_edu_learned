#include <stdio.h>

//typedef int[10]     t;
//t * a;
//

int a[10] = {100, 200};

int b[5][10];

int (*pb[5])[10];

int main(void)
{
    //int * p[10];
    int (*p2)[10];

    p2 = &a;

    printf("p2 = 0x%x\n", (int)p2);
    printf("p2+1 = 0x%x\n", (int)(p2+1));

    printf("p2[0] = %d\n", (*p2)[0] );
    printf("p2[0] = %d\n", p2[0][0] );

    pb[0] = &b[0];

    pb[1] = &b[1];

    return 0;
}
