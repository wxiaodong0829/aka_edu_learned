#include <stdio.h>

void sort1(int num[10])
{
    int i, j, tmp;

    for (i = 0; i < 10; i++)
    {       
        for (j = 9; j >= i; j--)
        {
            if (num[j - 1] > num[j])      
                tmp = num[j];
            num[j] = num[j - 1];
            num[j - 1] = tmp;
        }
    }
    printf("sort1:\n");
    for (i = 0; i < 10; i++)
        printf("%d ", num[i]);
    printf("\n");
}

void sort2(int num[10])
{

}
int main()
{  
    int i;
    int num[10] = {9, 5, 6, 7, 1, 2, 3, 0, 8, 4};

    printf("pre sort:\n");
    for (i = 0; i < 10; i++ )
    {
        printf("%d ", num[i]);
    }
    printf("\n");
    sort1(num);
    sort2(num);
    return 0;
}
