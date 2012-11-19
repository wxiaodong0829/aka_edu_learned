#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void err_sys(const char *str)
{
    perror(str);
    exit(1);
}

int main(void)
{
    DIR *dp;
    struct dirent *p;

    dp = opendir(".");
    if(dp == NULL)
        err_sys("opendir error");

    while(1){
        p = readdir(dp);
        if(p == NULL)
            break;
        if(p->d_name[0] != '.')
            printf("%s\n", p->d_name);
    }

    closedir(dp);

    return 0;
}
