#include <stdio.h>
#include <stdlib.h>

#define LEN 8
int a[LEN] = {5,2,4,7,1,3,2,6};

void merge(int start, int end, int mid)
{
    int left_len, right_len;
    int *left, *right;
    int i, j, k;

    left_len = mid - start + 1;
    right_len = end - mid;

    left = (int *)malloc(sizeof(int) * left_len);
    right = (int *)malloc(sizeof(int) * right_len);

    for(i = 0; i < left_len; i++)
        left[i] = a[start + i];
    for(j = 0; j < right_len; j++)
        right[j] = a[mid + 1 + j];

    i = 0, j = 0, k = start;
    while(i < left_len && j < right_len){
        if(left[i] < right[j]){
            a[k] = left[i];
            k++, i++;
        }else{
            a[k] = right[j];
            k++, j++;
        }
    }
    while(j < right_len)
        a[k++] = right[j++];
    while(i < left_len)
        a[k++] = left[i++];

    free(left);
    free(right);
}

void sort(int start, int end)
{
    int mid;

    if(start < end){
        mid = (start + end) / 2;
        sort(start, mid);
        sort(mid + 1, end);
        merge(start, end, mid);
    }
}

int main(void)
{
    int i;

    sort(0, LEN - 1);
    for(i = 0; i < LEN; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}


