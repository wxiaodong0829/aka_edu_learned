#include <stdio.h>
#define BUFSIZE 100
static char buf[BUFSIZE];
static int bufp = 0;
int getch()
{
    return (bufp>0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
    buf[bufp++] = c;
}
