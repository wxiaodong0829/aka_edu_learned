#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
int main()
{
    int type;
    double op2;
    char s[MAXOP];
    while ((type=getop(s))!=EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s)); break;
            case '+':
                push(pop()+pop()); break;
            case '*':
                push(pop()*pop()); break;
            case '-':
                op2 = pop(); push(pop()-op2); break;
            case '/':
                op2 = pop(); push(pop()/op2); break;
            case '\n':
                printf("\t%.8g\n", pop());
            default: break;
        }
    }
    return 0;
}
