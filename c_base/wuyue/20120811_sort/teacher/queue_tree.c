#include <stdio.h>

typedef struct
{
    char ch;
    int l, r;
}node_t;

node_t queue[512];
int head = -1, tail = -1;

void enqueue(node_t n)
{
    queue[++tail] = n;
}

node_t dequeue(void)
{
    return queue[++head];
}

int is_empty(void)
{
    return head == tail;
}

int main(void)
{
    node_t tree[7] = {{'A', 1, 2}, {'B', 3,4}, 
        {'C', 5, 6}, {'D', -1,-1}, {'E', -1,-1},
        {'F', -1, -1}, {'G', -1, -1}};
    node_t item;

    enqueue(tree[0]);
    while(is_empty() == 0){
        item = dequeue();
        putchar(item.ch);
        if(item.l != -1)
            enqueue(tree[item.l]);
        if(item.r != -1)
            enqueue(tree[item.r]);
    }
    putchar('\n');

    return 0;
}
