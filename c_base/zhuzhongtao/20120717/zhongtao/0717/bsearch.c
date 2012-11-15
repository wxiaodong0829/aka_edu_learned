#include <stdio.h>
int a[] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 
    43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
void primes(int n)
{
    int i, j;
    printf("2\n");
    for (i=3; i<=n; i+=2) {
        for (j=2; j*j<i; j++) if (i%j==0) break;
        if (j*j>i) printf("%d\n", i);
    }
}
int bsearch(int key, int l, int r)
{
    int m;
    while (l<=r) {
        m = (l+r)/2;
        if      (key<a[m]) r = m - 1;
        else if (key>a[m]) l = m + 1;
        else return m;
    }
    return -1;
}
int search(int key, int l, int r)
{
    int m;
    while (l<=r) {
        m = (l+r)/2;
        if (key<a[m]) r = m - 1;
        else          l = m + 1;
    }
    if (key==a[r]) return r;
    else           return -1;
}
int main()
{
//    primes(100);
    printf("%d\n", bsearch(50, 0, sizeof(a)/sizeof(int)-1));
    return 0;
}
