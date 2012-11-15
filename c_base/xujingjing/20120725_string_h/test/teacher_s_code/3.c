#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmp_str(const void *s1, const void *s2)
{
    return strcmp(*(char **)s1, *(char **)s2);
}

int main(void)
{
    char *strp[] = {"Wuhanaeghapoegh", "Shanghaieagaga", "Tianjin", "Beijing"};
    int i;
    qsort(strp, 4, 4, cmp_str);

    for(i = 0; i < 4; i++)
        printf("strp[%d] = %s\n", i, strp[i]);
    return 0;
}
