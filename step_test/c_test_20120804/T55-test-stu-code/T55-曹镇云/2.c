#include<stdio.h>
#include<stdlib.h>

void print(int num[])
{
    int i;
    for(i=0; i<10; i++)
        printf("%3d", num[i]);
    printf("\n");
}
void swap(int num[],int a, int b)
{
    int tmp;
    tmp = num[a];
    num[a] = num[b];
    num[b] = tmp;
    
}

int sort_buddle(int num[])
{
    int i, j;
    for(i=10; i>0; i--)
    {
        for(j=0; j<10; j++)
        {
            if(num[j]>num[j+1])
                swap(num, j, j+1);
        }
        j=0;
        print(num);
    }
    
}

int sort_select(int num[])
{
    int i, j;
    for(i=0; i<10; i++)
    {
        for(j=i+1; j<10; j++)
        {
            if(num[i]>num[j])
                swap(num, i, j);
        }
        print(num);
    }
}

int main(void)
{
    int i;
    int num[10];

    for(i=0; i<10; i++)
        num[i]=(rand()%100);
    print(num);

    printf("buddle\n");
    sort_buddle(num);

    printf("-----------------------------------\n");
    for(i=0; i<10; i++)
        num[i]=rand()%100;
    print(num);

    printf("selection\n");
    sort_select(num);

    return 0;

}

