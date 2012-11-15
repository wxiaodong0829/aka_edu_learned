#include <stdio.h>
#include <stdlib.h>

#define LEN 1 
typedef struct node{
    int n;
    struct node *next;
}node_t;

node_t *create(node_t *head, int len)
{
    int i;
    node_t *cur, *tail;

    for(i = 0; i < len; i++){
        cur = malloc(sizeof(node_t));
        scanf("%d", &(cur->n));
        cur->next = NULL;
        if(i == 0)
            head = cur;
        else
            tail->next = cur;
        tail = cur;
    }
    return head;
}

node_t *reverse(node_t *head)
{
    node_t *pre, *next, *cur;
    int i = 1;

    pre = head;
    cur = next = head->next;
    while(cur){
        printf("i = %d\n", i++);
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    head->next = NULL;
    head = cur;
    return pre;
}

int main(void)
{
    node_t *head = NULL, *cur, *del;
    head = create(head, LEN);

    for(cur = head; cur != NULL; cur = cur->next){
        printf("--%d--", cur->n);
    }
    printf("\n");
    head = reverse(head);

    cur = head;
    while(cur != NULL){
        printf("==%d==", cur->n);
        del = cur;
        cur = cur->next;
        free(del);
    }
    printf("\n");
    return 0;
}
