#include <stdio.h>
#define N 5
#define M 5


void init(int n[][M])
{
    int i, j;
    srand(time(NULL));
    for (i=0; i<N; i++)
        for (j=0; j<M; j++)
        n[i][j] = rand()%100;
}


void putit(int n[][M])
{
    int i, j;
    for (i=0; i<N; i++) {
        for (j=0; j<M; j++)
            printf("%4d", n[i][j]);
        printf("\n");
    }
}


/*void swap(int n[], int i, int j)
{
    int tmp;
    tmp = n[i];
    n[i] = n[j];
    n[j] = tmp;
}


void csort(int n[])
{
    int i, j, tmp;
    for (i=0; i<N-1; i++) {
        tmp = i;
        for (j=i+1; j<N; j++)
            if (n[tmp] > n[j])
                tmp = j;
        if (i != tmp)
            swap(n, i, tmp);
    }
}*/

void swap(int *n, int i, int j)
{
    int tmp;
    tmp = *(n+i);
    *(n+i) = *(n+j);
    *(n+j) = tmp;
}
void csort(int * n, int m)
{
    int i, j, tmp;
    for (i=0; i<m-1; i++) {
        tmp = i;
        for (j=i+1; j<m; j++)
            if (*(n+tmp) > *(n+j))
                tmp = j;
        if (i != tmp)
            swap(n, i, tmp);
    }
}

int main(void)
{
    int arr[N][M];
    int i;

    init(arr);
    putit(arr);
    printf("\n");

    for (i=0; i<N; i++)
        csort(arr[i], M);
    putit(arr);
    printf("\n");

    csort((int *)arr, N*M);
    putit(arr);

    return 0;
}
