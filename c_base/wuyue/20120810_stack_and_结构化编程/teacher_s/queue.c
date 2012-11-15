#include <stdio.h>

int queue[512];
int head = -1, tail = -1;
void enqueue(int i)
{
    tail++;
    queue[tail] = i;
}
int dequeue(void)
{
    head++;
    return queue[head];
}
int is_empty()
{
    return head == tail;
}
int main(void)
{
    int n;
    while(1){
        scanf("%d", &n);
        if(n == -1)
            break;
        enqueue(n);
    }
    while(is_empty() == 0){
        n = dequeue();
        printf("%d ", n);
    }
    printf("\n");

    return 0;
}
