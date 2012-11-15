#include <stdio.h>
#include <string.h>

int main(void)
{
    char src1[] = "abcd;bcde:,cde:de";
    char src2[] = "root/abcd/akaedu";
    char *token1, *token2, *savep1, *savep2;

    token1 = strtok_r(src1, ",:;", &savep1);
    printf("token1:%s\n", token1);

    token2= strtok_r(src2, "/", &savep2);
    printf("token2%s\n", token2);

    token1 = strtok_r(NULL, ",:;", &savep1);
    printf("token1:%s\n", token1);

    
    return 0;
}
