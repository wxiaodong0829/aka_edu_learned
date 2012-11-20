#include <stdio.h>
#include <string.h>
#define N 100
void get_str(char s[], int n)
{
    int i=0;
    char c;

    while (--n > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    
    s[i] = '\0';
}


void sort(char s[])
{
    char alpha[N];
    char other[N];
    int i, j, k;
    j = 0, k = 0;
    for (i=0; s[i]; i++) {
        if (isalpha(s[i]))
            alpha[j++] = s[i];
        else
            other[k++] = s[i];
    }
    alpha[j] = '\0';
    other[k] = '\0';
    strcat(alpha, other);
    strcpy(s, alpha);
}


int main(void)
{
    char str[N];
    
    get_str(str, N);

    sort(str);
    puts(str);

    return 0;
}
