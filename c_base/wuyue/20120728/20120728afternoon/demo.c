#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* demo-1
int main(void)
{
    int i = 1;

    printf("%d, %d\n", i, ++i);

    return 0;
}
*/

/* demo-2
int main(void)
{
    char buf[8];

    strcpy(buf, "hello world hello akaedu");
    printf("%s\n", buf);
    exit(0);

    return 0;
}
*/

/* demo-3
int main(void)
{
    char buf[] = "hello world";

    strcpy(&buf[2], buf);
    printf("%s\n", buf);

    return 0;
}
*/

int main(void)
{
    int i;

    i = printf("hello world\n");
    //return 0;
}
