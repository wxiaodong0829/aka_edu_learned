#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_PATH 1024

int count(const char *root)
{
    int total = 0, n;
    DIR *dp;
    struct dirent *p;
    char path[MAX_PATH];
    struct stat statbuf;

    dp = opendir(root);
    if(dp == NULL)
        return -1;
    while(p = readdir(dp)){
        if(strcmp(p->d_name, ".") == 0 
        || strcmp(p->d_name, "..") == 0)
            continue;
        sprintf(path, "%s/%s", root, p->d_name);
        n = lstat(path, &statbuf);
        if(n == -1)
            return -1;
        if(S_ISREG(statbuf.st_mode))
            total++;
        else if(S_ISDIR(statbuf.st_mode)){
            n = count(path);
            if(n == -1)
                return -1;
            total += n;
        }
    }
    closedir(dp);

    return total;
}

int main(int argc, char *argv[])
{
    char *root = ".";
    int total;

    if(argc == 2)
        root = argv[1];
    total = count(root);
    if(total == -1)
	    return -1;
    printf("total : %d\n", total);

    return 0;
}
