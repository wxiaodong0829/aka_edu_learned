/*************************************************************************
    > File Name: find.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月11日 星期六 17时24分12秒
 ************************************************************************/

#include <stdio.h>

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
