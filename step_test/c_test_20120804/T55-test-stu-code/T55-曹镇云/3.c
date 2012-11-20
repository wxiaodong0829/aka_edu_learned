#include<stdio.h>
#include<stdlib.h>


void init(int arr[5][5])
{
    int i, j;
    for(i=0; i<5; i++)
    {
        for(j=0; j<5; j++)
            arr[i][j]=(rand()%100);
    }

}

void print(int arr[5][5])
{
    int i, j;
    for(i=0; i<5; i++)
        for(j=0; j<5; j++)
            printf("%3d%s", arr[i][j], j%5==4?"\n":"");
    printf("\n");
}

void swap(int num[5][5], int line, int a, int b)
{
    int tmp;
    tmp = num[line][a];
    num[line][a] = num[line][b];
    num[line][b] = tmp;
    
}

int sort_select(int arr[5][5], int flag)
{
    int i, j, line;
    if(flag==0)
    {
        for(line=0; line<5; line++)
        {
            for(i=0; i<5; i++)
                for(j=i+1; j<5; j++)
                {
                    if(arr[line][i]>arr[line][j])
                        swap(arr, line, i, j);
                }
        }
    }
#if 0
    else if(flag==1)
    {
        for(i=0; i<5; i++)
            for(j=i+1; j<5; j++)
            {
                if(arr[i][i]>arr[i][j])
                    swap(arr, i, j);
            }

    }
#endif
}
int main(void)
{
    int arr[5][5];

    init(arr);
    print(arr);

    printf("line sort:\n");
    sort_select(arr, 0);
    print(arr);
    printf("------------");
#if 0
    printf("single sort:");
    sort_select(arr, 1);
    print(arr);
#endif


    return 0;
}

