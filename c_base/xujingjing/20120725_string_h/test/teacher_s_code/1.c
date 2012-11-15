#include <stdio.h>

int main(void)
{
    char str[2][20], max;
    int i, j;

    for(i = 0; i < 2; i++)
        scanf("%s", str[i]);

    max = str[0][0];
    for(i = 0; i < 2; i++)
        for(j = 0; str[i][j]; j++)
            if(max < str[i][j])
                max = str[i][j];

    printf("max = %c\n", max);
    return 0;
}
