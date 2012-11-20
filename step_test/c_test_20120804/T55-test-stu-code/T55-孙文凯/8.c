#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void dollars(char *dest, char const *src)
{
    int i, j, len;
    char p[100];
    for (i=0; src[i]; i++)
        p[i] = src[i];
    p[i] = '\0';
    len = strlen(src);
    if (len == 1) {
        dest[0] = '$';
        dest[1] = '0';
        dest[2] = '.';
        dest[3] = '0';
        dest[4] = src[0];
    }
    if (len == 2) {
        dest[0] = '$';
        dest[1] = '0';
        dest[2] = '.';
        dest[3] = src[0];
        dest[4] = src[1];
    }
    if (len >= 3) {
        reverse(p);
        dest[0] = p[0];
        dest[1] = p[1];
        dest[2] = '.';
        for (i=2, j=3; i< len; i++) {
            dest[j++] = p[i];
            if (i != len-1 && (i-1)%3 == 0)
                dest[j++] = ',';
        }
        dest[j] = '$';
        reverse(dest);
    }
    puts(dest);
}
int main(void)
{
    char *src;
    char *dest;

    src = malloc(64); 
    dest = malloc(64);

    scanf("%s", src);
    dollars(dest, src);

    free(src);
    free(dest);


    return 0;
}
