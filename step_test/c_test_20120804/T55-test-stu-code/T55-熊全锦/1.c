#include<stdio.h>

int myadd(int n)
{
    int i, j, flag = 0, sum = 0;
    for(i=n; i > 1; i--)
    {
        for(j = 0; j*j<= i; j++)
        {

        if(i % j == 0)
        {  flag = 0;
            sum += 0;
        }

        else if(i % j != 0)
            flag = 1;

        }
        if(flag == 1)
            sum += i;

    }
    return sum;
}

int main()
{
    int n;
    printf("please input n:\n");
    scanf("%d\n",&n);
    printf("%d\n",n);
    printf("%d\n",myadd(n));
    return 0;
}

