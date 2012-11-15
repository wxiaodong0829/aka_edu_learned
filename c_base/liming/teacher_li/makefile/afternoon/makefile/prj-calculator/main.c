#include <stdio.h>
#include "head.h"

int main(void)
{
    int a = 100;
    int b = 200;

    printf("PI = %f\n", PI);

    printf("a + b = %d\n", add(a, b));
    printf("a - b = %d\n", sub(a, b));

    return 0;
}

