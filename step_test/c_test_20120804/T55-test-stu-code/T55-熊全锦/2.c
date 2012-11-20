#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int num[10];

void mysrand()
{
    int i;
    srand(time(NULL));
    for (i = 0; i < 10; i++)
    {
        num[i] = rand();
        printf("%d\t",num[i]);

    }
    printf("\n");
    
}
#if 0 
int *bub_sort()
{
    int j, k, tmp;
    for(j = 0; j < 9; j++)
    {
        for(k = 0; k < 10 - j; k++)
        {
            if(num[k] >= num[k+1] )
            { tmp = num[k]; num[k] = num[k+1]; num[k+1] = tmp;}
        }

    }

return num;

}
#endif
#if 0 
int *slec_sort()
{
    int m , n, flag, min, tmp;
    for(m = 0; m < 10; m++)
    {
            min = num[m];
            flag = m;
        for(n = m+1; n < 10; n++)
        {
            if( num[n] <= min)
            {
                min = num[n];
                flag = n;
            }

        }
        tmp = num[m];
       num[m] = num[flag];
        num[flag] = num[m];

    }
return num;
}
#endif


int main()
{
    int l;
    mysrand();
    for(l = 0; l < 10; l++)
    {
        printf("%d\t",*(slec_sort()+l));
    }

    return 0;
}
