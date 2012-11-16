#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

ssize_t read_line(int fd, void *buf, size_t count)
{
    int i, n;
    char *p;

    p = (char *)buf;
    for(i = 0; i < count; i++){
        n = read(fd, p, sizeof(char));
        if(n == -1)
            return -1;
        else if(n == 0)
            break;
        else{
            if(*p == '\n')
                break;
            else
                p++;
        }
    }
    if(i > 0) i++;
    
    return i;
}

void err_sys(const char *str)
{
    perror(str);
    exit(1);
}

int main(void)
{
    int fd;
    char buf[1024];
    FILE *fp;
#ifdef TEST
    fd = open("test.txt", O_RDONLY);
    if(fd == -1)
        err_sys("open error");
    while(read_line(fd, buf, 1024));
    close(fd);
#else
    fp = fopen("test.txt", "r");
    if(fp == NULL)
        err_sys("fopen error");
    while(fgets(buf, 1024, fp));
    fclose(fp);
#endif
    return 0;
}
