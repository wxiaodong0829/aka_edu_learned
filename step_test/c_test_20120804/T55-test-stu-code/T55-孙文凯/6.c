#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char *p)
{
    int i, n, line;
    char tmp;
    n = strlen(p)-1;
    for (i=0; i < n; i++,n--) {
        tmp = p[i];
        p[i] = p[n];
        p[n] = tmp;
    }
}
char *myitoa(int n, char *p)
{
    int tmp, num, i;
    char ch, flag;
    flag = ' ';
    i = 0;
    if (n < 0) {
        flag = '-';
        n = -n;
    }
    while (n > 0) {
        p[i++] = n%10 + '0';
        n = n/10;
    }

    if (flag == '-')
        p[i++] = '-';
    p[i] = '\0';

    reverse(p);

    return p;

}
int main(void)
{
    char *p;
    int num;

    p = malloc(64);
    scanf("%d", &num);

    p = myitoa(num, p);
    puts(p);
    free(p);
    return 0;
}
