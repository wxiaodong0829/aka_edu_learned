#include <stdio.h>
#include <string.h>

int main(void)
{
    char *p = "hello";
    char s[] = "hello";

    sizeof(p), sizeof(s);
    strlen(p), strlen(s);

    char q[30] = "hello";
    printf("%d, %d\n", sizeof(q), strlen(q));

    return 0;
}
