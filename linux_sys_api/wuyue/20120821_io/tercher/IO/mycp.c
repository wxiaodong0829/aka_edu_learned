#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define NEW_PERM 0644

void err_sys(const char *str)
{
    perror(str);
    exit(1);
}

void err_usr(const char *str)
{
    fputs(str, stderr);
    exit(2);
}

/* ./mycp src dst */
int main(int argc, char *argv[])
{
    int src, dst;
    char buf[1024]; int n;

    if(argc != 3)
        err_usr("usage: ./mycp src dst\n");

    src = open(argv[1], O_RDONLY);
    if(src == -1)
        err_sys("open error");
    dst = open(argv[2], 
        O_WRONLY | O_CREAT | O_TRUNC, NEW_PERM);
    if(dst == -1)
        err_sys("open error");

    while(n = read(src, buf, 1024))
        write(dst, buf, n);

    close(src);
    close(dst);

    return 0;
}
