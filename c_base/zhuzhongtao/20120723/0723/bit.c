#include <stdio.h>
int main()
{
    struct {
        unsigned is_keyword : 10;
        unsigned is_extern  : 20;
        unsigned is_static  :  2;
    } flags;
    printf("%d\n", sizeof(flags));
    return 0;
}
