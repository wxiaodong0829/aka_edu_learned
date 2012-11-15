#include <stdio.h>
#include <string.h>
int i=0;
int eval1(char s[])
{
    while (s[i]==' ') i++;
    if (s[i]>='0' && s[i]<='9') return s[i++]-'0';
    if (s[i]=='+') { i++; return eval1(s)+eval1(s); }
    if (s[i]=='*') { i++; return eval1(s)*eval1(s); }
}
int eval2(char *s)
{
    static char *p; p = s;
    while (*p==' ') p++;
    if (*p>='0' && *p<='9') return *p++ - '0';
    if (*p=='+') { p++; return eval2(p)+eval2(p); }
    if (*p=='*') { p++; return eval2(p)*eval2(p); }
}
int main()
{
    printf("%d\n", eval1("* + 2 3 4"));
    printf("%d\n", eval2("* + 2 3 4"));
    return 0;
}
