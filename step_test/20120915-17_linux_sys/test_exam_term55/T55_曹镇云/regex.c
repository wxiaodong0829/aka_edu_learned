#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<regex.h>

int main(int argc, char *argv[])
{
    char *pat;
    char ebuf[128], lbuf[256];
    int z, i;
    const char *regex = "h=^[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.$'";
    regex_t reg;
    regmatch_t pm[10];
    const size_t nmatch = 10;

    z = regcomp(&reg, regex, 0);
    if(z != 0)
    {
        perror("regcomp");
        exit(1);
    }

    z = regexec(&reg, argv[1], nmatch, pm, 0);

    if(z == REG_NOMATCH)
    {
        return 0;
    }
    else{
        for(i = 0; i < nmatch && pm[i].rm_so != -1; ++i)
            printf("%s\n", argv[1]);
    }
    regfree(&reg);

    return 0;



}
