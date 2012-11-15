#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int *S, top;
void init_stack(int n)
{
    S = malloc(n * sizeof(int));
    top = 0;
}
void push(int v) { S[top++] = v; }
int pop() { return S[--top]; }
int eval(char s[])
{
    int i, n=strlen(s);
    init_stack(n);
    for (i=0; i<n; i++) {
        if (s[i]>='0' && s[i]<='9') push(s[i]-'0');
        if (s[i]=='+') push(pop()+pop());
        if (s[i]=='*') push(pop()*pop());
    }
    return pop();
}
int main()
{
    printf("%d\n", eval("1 2 + 3 4 + *"));
    return 0;
}
