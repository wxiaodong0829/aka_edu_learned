#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *p;
    printf("strstr(\"%s\", \"%s\"):%s\n", argv[1], argv[2],
            p = strstr(argv[1], argv[2]));

    printf("argv[1]:%p, %s\n", argv[1], argv[1]);
    printf("p:%p, %s\n", p, p);
    return 0;
}
