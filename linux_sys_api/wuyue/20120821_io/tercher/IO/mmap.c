#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(void)
{
    int fd, i;
    char *p;
    
    fd = open("test.txt", O_RDWR);
    p = (char *)mmap(NULL, 6, 
        PROT_READ | PROT_WRITE, 
        MAP_SHARED, fd, 0);
    p[2] = 'L';

    return 0;
}
