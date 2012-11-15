#include <string.h>
#include "mem.h"
static char buf[MAXBUF+MAXLINE];
static char *f=buf, *r=buf;
void put(char *s)
{
    strcpy(r, s);
    r += strlen(s) +1;
    if (r>=buf+MAXBUF) r = buf;
}
char *get()
{
    char *p = f;
    f += strlen(p) + 1;
    if (f>=buf+MAXBUF) f = buf;
    return p;
}
