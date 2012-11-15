#include <stdio.h>

#define PRINT(x)    printf("(%s)debug> " #x" = 0x%x (%c)\n",__func__, x, x)

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


int main(void)
{
    char buf[10] = "qwer";
    char * p;
    char c = '9';

//    p = "ab34";
//    p = buf;
//    p = malloc(10);
//    strcpy(p, "abcd");

    p = &c;
#if 0
#endif

    PRINT(p);
    PRINT(&p);
    test(p);
    PRINT(p);
    PRINT(&p);
    return 0;

    PRINT(c);
    PRINT(*(p+1));

    PRINT(buf[0]);
    PRINT(buf[1]);
    return 0;
}
