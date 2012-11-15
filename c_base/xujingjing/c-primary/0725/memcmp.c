#include <stdio.h>
#include <string.h>

int  main(void)
{
    char *src = "abcdefg";
    int num[] = {'a', 'b', 'c', 'd'};

    printf("memcmp:%d\n", memcmp(src, num, 4));
    return 0;
}
