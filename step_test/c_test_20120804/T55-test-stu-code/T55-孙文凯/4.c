#include <stdio.h>
#define N 100
void get_str(char s[], int n)
{
    int i=0;
    char c;

    while (--n > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    
    s[i] = '\0';
}
int find_bigest(char str[])
{
    char ch;
    int i, big;
    
    ch = str[0];
    big = 0;
    
    for (i=1; str[i]; i++)
        if (ch < str[i]) {
            ch = str[i];
            big = i;
        }

    return big;
}
void move(char str[], int n)
{
    char tmp;
    int i;

    tmp = str[n];

    for (i=n; i>0; i--)
        str[i] = str[i-1];

    str[0] = tmp;

}
int main(void)
{
    char str[N];

    get_str(str, N);

    move(str, find_bigest(str));

    puts(str);

    return 0;
}
