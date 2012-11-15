#include <stdio.h>
#include <string.h>
#define M 10000
#define N 1000
char buf[M];
char *A[N];
void swap(char *a[], int i, int j)
{
     char *tmp = a[i]; a[i] = a[j]; a[j] = tmp;
}
int partition(char *a[], int l, int r)
{
    int i, j;
    for (j=l, i=l+1; i<=r; i++)
        if (strcmp(a[i],a[l])<0) swap(a, i, ++j);
    swap(a, l, j);
    return j;
}
void sort(char *a[], int l, int r)
{
    if (l>=r) return;
    int k = partition(a, l, r);
    sort(a, l, k-1);
    sort(a, k+1, r);
}
int main()
{
    int i, j=0;
    for (i=0; i<N; i++) {
        A[i] = &buf[j];
        if (scanf("%s", A[i])==EOF) break;
        j += strlen(A[i])+1;
    }
    sort(A, 0, i-1);
    for (j=0; j<i; j++) printf("%s\n", A[j]);
    return 0;
}
