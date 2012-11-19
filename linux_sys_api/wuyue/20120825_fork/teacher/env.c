#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *p;

    p = getenv("LOGNAME");
    if(p == NULL)
        printf("not found\n");
    else
        printf("%s\n", p);

    setenv("LOGNAME", "haha", 0);

    p = getenv("LOGNAME");
    if(p == NULL)
        printf("not found\n");
    else
        printf("%s\n", p);

    return 0;
}
