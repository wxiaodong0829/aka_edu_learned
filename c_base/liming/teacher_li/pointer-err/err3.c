#include <stdio.h>

#define PRINT(x)    printf("(%s)debug> " #x" = 0x%x (%c)\n",__func__, (int)x, (int)x)

void test(char * p)
{
    char c;

    PRINT(p);
    PRINT(&p);
    p = (char *)0;
    PRINT(p);
    PRINT(&p);
    return;

//    *p = 'a';
    *p = 'a';
    c = *p;
    printf("c = %c\n", c);

    *(p+1) = 'b';
    c = *(p+1);
    printf("c = %c\n", c);
    return;
}

char * head;

void getp(char * *p)
{
    static char c = '8';
    //*p = 0x1234;
    printf("p = 0x%x\n", p);
//    *p = 0x1234;
//    *p = &c;
    //*p = head;
    *p = malloc(2);
    *p[0] = '6';

    return;
}

int main(void)
{
    int a;
    char buf[10] = "qwer";
    char * p;
    char * argv[10];
    char * p1;

    head = (char *)malloc(2);
    head[0] = '7';
    printf("p1 = 0x%x\n", p1);
    printf("&p1 = 0x%x\n", &p1);
    getp(&p1);
    
    a = (int)p1;
    free(p1);
    //free(a);
    printf("p1 = 0x%x\n", p1);
    printf("*p1 = %c\n", *p1);

    return 0;

    parse(buf, argv);

    return 0;
}
