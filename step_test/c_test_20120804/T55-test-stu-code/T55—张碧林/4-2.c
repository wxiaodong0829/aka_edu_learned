#include <stdio.h>
#include <time.h>
#define N 10
#define M 100

void init(int *num)
{

   int i;
   srand(time(NULL));
   for(i = 0; i < N; i++)
   {
        num[i] = rand()%M;
   }
}

void show(int *num) 
{
    int i;
    for(i = 0; i < N; i++)
        printf("%4d", num[i]);
    printf("\n");

}

void sort_sel(int *num)
{
    int i, j, tmp;
    for(i = 0; i < N; i++)
    {
        for(j = i+1; j < N; j++) 
                if(num[i] < num[j])
                {
                    tmp = num[i]; 
                    num[i] = num[j];
                    num[j] = tmp;
                }
    }

}
void sort_mp(int *num)
{
    int i, j, tmp;
    for(i = 0; i < N-1; i++)
    {
        for(j = 0; j < N - i -1; j++) 
        {
            if(num[j] < num[j+1]) 
            {
                tmp = num[j];
                num[j] = num[j+1];
                num[j+1] = tmp;
            }
        }
    }
}
int main(void)
{
    int num[N];
    init(num);
    show(num);
//    sort_sel(num);
    sort_mp(num);
    show(num);
   
   return 0;
}
