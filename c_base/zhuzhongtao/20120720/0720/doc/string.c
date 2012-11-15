#include <stdio.h>
#include <string.h>
int main()
{
    char s[] = "now is the time for all";
    int i, n=strlen(s);
    printf(".PS\n");
    printf("boxwid=.2\n");
    printf("boxht=.3\n");
    for (i=0; i<n; i++)
        printf("box \"%c\"\n", s[i]);
    printf(".PE\n");
}
