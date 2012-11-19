#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "err.h"

int main(int argc, char *argv[])
{
    int in, out;
    char *s, *d;
    int len, i;

    if(argc != 3)
        err_usr("usage: ./mycp src dst\n");

    in = open(argv[1], O_RDONLY);
    if(in == -1)
        err_sys("open error");
    out = open(argv[2], 
        O_RDWR | O_CREAT | O_TRUNC, 0644);/*如果是只写，则不能建立映射区*/
    if(out == -1)
        err_sys("open error");

    len = lseek(in, 0, SEEK_END);
    s = (char *)mmap(NULL, len, 
        PROT_READ, MAP_PRIVATE, in, 0);
    if(s == MAP_FAILED)
        err_sys("mmap error");

    lseek(out, len - 1, SEEK_SET);
    write(out, "a", 1);
    d = (char *)mmap(NULL, len, 
        PROT_WRITE, MAP_SHARED, out, 0);
    if(d == MAP_FAILED)
        err_sys("mmap error");
    close(in); close(out);

    for(i = 0; i < len; i++)
        d[i] = s[i];

    munmap(d, len);
    munmap(s, len);

    return 0;
}
