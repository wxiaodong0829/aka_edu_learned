#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 13
int a[N];
void init(int l, int r)
{
    int i;
    srand(time(NULL));
    for (i=l; i<=r; i++) a[i] = rand()%100;
}
void show(int l, int r)
{
    int i;
    for (i=l; i<=r; i++) printf("%3d", a[i]);
    printf("\n");
}
void insertion(int l, int r)
{
    int i, j; int tmp;
    for (j=l+1; j<=r; j++) {
        tmp = a[j];
        for (i=j-1; i>=l && tmp<a[i]; i--) a[i+1] = a[i];
        a[i+1] = tmp;
    }
}
void shell(int l, int r)
{
    int i, j, gap; int tmp;
    for (gap=(r-l+1)/2; gap>=1; gap/=2) {
        for (j=l+gap; j<=r; j++) {
            tmp = a[j];
            for (i=j-gap; i>=l && tmp<a[i]; i-=gap)
                a[i+gap] = a[i];
            a[i+gap] = tmp;
        }
        show(0, N-1);
    }
}
#define sort shell
int main()
{
    init(0, N-1);
    show(0, N-1);
    printf("\n");
    sort(0, N-1);
    return 0;
}
