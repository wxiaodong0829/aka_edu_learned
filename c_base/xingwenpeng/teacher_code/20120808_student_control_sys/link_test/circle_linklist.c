#include <stdio.h>
#include <stdlib.h>

#define NUM 10

typedef struct node{
    unsigned n;
    struct node *next;
}node_t;


node_t *create(node_t *head, int len)
{
    int i;
    node_t *cur, *tail;

    for(i = 0; i < len; i++){
        cur = malloc(sizeof(node_t));
        if(cur == NULL){
            perror("malloc fail");
            exit(1);
        }
        cur->n = i + 1;
        cur->next = NULL;
        if(i == 0)
            head = tail = cur;
        else{
            tail->next = cur;
            tail = cur;
        }
    }
    tail->next = head;
    return head;
}

int main(void)
{
    node_t *head = NULL, *cur, *pre;

    head = create(head, NUM);

    pre = cur = head;
    while(1){
        pre = pre->next;
        cur = cur->next->next;
        if(pre == NULL || cur == NULL){
            printf("No Ring!\n");
            return 0;
        }
        if(pre == cur){
            printf("Ring occurred!\n");
            return 0;
        }
    }
    return 0;
}
