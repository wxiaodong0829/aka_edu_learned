#include <stdio.h>

void bubble_sort(int a[], int n)
{
    int i, j, t;

    for(i = 0; i < n - 1; i++)
        for(j = 0; j < n - i - 1; j++)
            if(a[j] > a[j + 1]){
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
}

void insertation_sort(int a[], int n)
{
    int i, j, t;

    for(i = 1; i < n; i++){
        t = a[i];
        for(j = i - 1; j >= 0 && a[j] > t; j--)
            a[j + 1] = a[j];
        a[j + 1] = t;

#ifdef DEBUG
        printf("%dth : ", i);
        for(j = 0; j < n; j++)
            printf("%d ", a[j]);
        printf("\n");
#endif
    }
}

int linar_search(int a[], int n, int key)
{
    int i;

    for(i = 0; i < n; i++)
        if(a[i] == key)
            return i;
    return -1;
}

int binary_search(int a[], int n, int key)
{
    int mid;
    int start, end;

    start = 0, end = n - 1;
    while(start <= end){
        mid = (start + end) / 2;
        if(key < a[mid])
            end = mid - 1;
        else if(key > a[mid])
            start = mid + 1;
        else
            return mid;
    }
    return -1;
}

#ifdef DEBUG
int main(void)
{
    int a[] = {5,4,2,3,1}, i;
    int pos;

    insertation_sort(a, 5);
    for(i = 0; i < 5; i++)
        printf("%d ", a[i]);
    printf("\n");

    pos = linar_search(a, 5, 4);
    if(pos == -1)
        printf("not found\n");
    else
        printf("%dth\n", pos + 1);

    return 0;
}
#endif
