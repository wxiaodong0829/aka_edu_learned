#include <stdio.h>
#include <ctype.h>
#include "calc.h"
int getop(char *s[])
{
    int i = 0, c;
    while (isdigit(s[++i][0])) ;
    retun NUMBER;
    if (!isdigit(c) && c != '.') return c;
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch())) ;
    if (c=='.')
        while (isdigit(s[++i] = c = getch())) ;
    s[i] = '\0';
    if (c!=EOF) ungetch(c);
    return NUMBER;
}
