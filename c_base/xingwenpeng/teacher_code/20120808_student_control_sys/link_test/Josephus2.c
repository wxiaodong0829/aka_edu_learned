#include <stdio.h>
#include <stdlib.h>

#define PERSONS 10
#define COUNT 4

typedef struct node{
    int data;
    struct node *next;
}node_t;

node_t *make_node(int data, node_t *next)
{
    node_t *cur = malloc(sizeof(node_t));
    cur->data = data;
    cur->next = next;
    return cur;
}

int main(void)
{
    int i;
    node_t *cur, *del;

    cur = make_node(1, NULL);
    cur->next = cur;

    for(i = 2; i <= PERSONS; i++)
        cur = cur->next = make_node(i, cur->next);

    while(cur != cur->next){
        for(i = 1; i < COUNT; i++)
            cur = cur->next;
        del = cur->next;
        cur->next = cur->next->next;
        printf("%d killed!\n", del->data);
        free(del);
    }
    printf("%d survived!\n", cur->data);
    return 0;
}
