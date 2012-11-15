#include <limits.h>
#include <stdio.h>
#include <string.h>
#define N 16
char s[N];
void reverse(char s[])
{
    int i, j, tmp;
    for (i=0, j=strlen(s)-1; i<j; i++, j--)
        tmp = s[i], s[i] = s[j], s[j] = tmp;
}
void itoa(unsigned n)
{
    int i=0, sign;
    if ((sign=n) < 0) n = -n;
    do {
        s[i++] = n % 10 + '0';
    } while ((n/=10) > 0);
    if (sign < 0) s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    printf("%s\n", s);
}
int main()
{
    itoa(INT_MIN);
    return 0;
}
