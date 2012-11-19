#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd, fd2;

    fd = open(...);
    fd2 = fd;

    if(access(argv[1], R_OK) == 0)
        printf("%s is readable\n", argv[1]);
    if(access(argv[1], W_OK) == 0)
        printf("%s is writable\n", argv[1]);
    if(access(argv[1], X_OK) == 0)
        printf("%s is executable\n", argv[1]);

    return 0;
}
