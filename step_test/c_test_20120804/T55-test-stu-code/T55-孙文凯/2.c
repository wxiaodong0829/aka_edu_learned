#include <stdio.h>
#include <time.h>
#define N 10



void init(int n[])
{
    int i;
    srand(time(NULL));
    for (i=0; i<N; i++)
        n[i] = rand()%100;
}


void putit(int n[])
{
    int i;
    for (i=0; i<N; i++)
        printf("%4d", n[i]);
    printf("\n");
}


void swap(int n[], int i, int j)
{
    int tmp;
    tmp = n[i];
    n[i] = n[j];
    n[j] = tmp;
}


void bsort(int n[])
{
    int i, j, tmp, flag;
    for (i=0; i<N-1; i++) {
        flag = 1;
        for (j=0; j<N-i-1; j++) {
            if (n[j] > n[j+1]) {
                swap(n, j, j+1);
                flag = 0;
            }
        }
        if (1 == flag)
            break;
    }
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
}


int main(void)
{
    int num[N];

    init(num);
    putit(num);
    bsort(num);
    putit(num);
    
    printf("\nwait 2s\n\n");
    sleep(2);

    init(num);
    putit(num);
    csort(num);
    putit(num);

    return 0;

}
