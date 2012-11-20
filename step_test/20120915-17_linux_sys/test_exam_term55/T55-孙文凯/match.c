#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <regex.h>
int match(const char *str)
{
    int n, cflags = REG_EXTENDED, eflags = 0;
    regex_t preg;
    regmatch_t pmatch[1];
    const size_t nmatch = 1;
    //char *regex = "^[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}.";
    char *regex = "^([0-9]{1,3}[.]){3}[0-9]{1,3}.";
    n = regcomp(&preg, regex, cflags);
    if (n != 0)
        return -1;

    n = regexec(&preg, str, nmatch, pmatch, eflags);
    regfree(&preg);
    if (n == 0)
        return 1;
    else if (n == REG_NOMATCH)
        return 0;
    else
        return -1;
}

int is_dir(const char *path)  /*  具体实现中没有用到这个函数  */
{
    struct stat buf;

    if (-1 == stat(path, &buf))
        return -1;

    if (S_ISDIR(buf.st_mode))
        return 1;

    return 0;
}

/*
int main(void)
{
    char buf[1024];
    int n;

    while (read(STDIN_FILENO, buf, 1024)) {
        buf[strlen(buf) - 1] = '\0';
        n = match(buf);
        if (n == 1)
            printf("match\n");
        else if (n == 0)
            printf("not match\n");
        else
            printf("match error\n");

    }

    return 0;
}
*/
