#include <stdio.h>
#include "mem.h"
#define min(a, b) (((a) < (b)) ? (a) : (b))
int main(int argc, char *argv[])
{
    char line[MAXLINE];
    int i, nlines = 0, ntail = 10;
    if (argc>1) {
        if (argv[1][0]=='-') ntail = atoi(argv[1]+1);
        if (ntail < 1) ntail = 10;
    }
    while ((scanf("%s", line))!=EOF) {
        put(line);
        if (++nlines > ntail) get();
    }
    for (i=0; i<min(nlines,ntail); i++) printf("%s\n", get());
    return 0;
}
