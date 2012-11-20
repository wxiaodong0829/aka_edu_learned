#include <stdio.h>
#include <time.h>
#define N1 5 
#define N2 5 
#define M 100

int nu[N1*N2];

void init(int num[N1][N2])
{

   int i, j;
   srand(time(NULL));
   for(i = 0; i < N1; i++)
           for(j = 0; j < N2; j++)
            {
                num[i][j] = rand()%M;
            }
}

void show(int num[N1][N2]) 
{
    int i, j;
    for(i = 0; i < N1; i++)
    {
            for(j = 0; j < N2; j++)
            {
                 printf("%4d", num[i][j]);
            }
        printf("\n");
    }
}
void show1(int *nu) 
{
    int i, j = 0;
    for(i = 0; i < N1*N2; i++)
    {
        printf("%4d", nu[i]);
        j += 1;
        if(j % 5 ==0)         
        {
        printf("\n");
        j = 0;
        }
    }
        printf("\n");
}
void sort_sel(int num[N1][N2])
{
    int i, j, k=0, tmp;
    for(i = 0; i < N1; i++ )
            for(j = 0; j < N2; j++)
            nu[k++] = num[i][j];
    for(i = 0; i < N1*N2; i++)
    {
          for(j = i+1; j < N1*N2; j++) 
            if(nu[i] < nu[j])
             {
                  tmp = nu[i]; 
                  nu[i] = nu[j];
                  nu[j] = tmp;
             }
    }

}
int main(void)
{
    int num[N1][N2];
    init(num);
    show(num);
   sort_sel(num);
   show1(nu);
   
   return 0;
}
