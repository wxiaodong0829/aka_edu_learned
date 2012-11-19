#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    struct stat buf;

    lstat(argv[1], &buf);
    if(S_ISREG(buf.st_mode))
        printf("regular file\n");
    else if(S_ISDIR(buf.st_mode))
        printf("dir file\n");
    else if(S_ISLNK(buf.st_mode))
        printf("symbol link file\n");
    else 
        printf("other...\n");

    return 0;
}
