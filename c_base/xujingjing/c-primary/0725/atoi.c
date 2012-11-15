#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("atoi(\"%s\") = %d\n", argv[1], atoi(argv[1]));
    return 0;
}
