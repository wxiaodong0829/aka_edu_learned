#include <stdlib.h>
#define N 1024
int main()
{
    int i;
    int **a = malloc(N*sizeof(int*));
    for (i=0; i<N; i++)
        a[i] = malloc(N*sizeof(int));
    a[i][j] = 0;
}
