#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}node_t;

node_t *make_node(int val)
{
    node_t *p = malloc(sizeof(node_t));
    if(p){
        p->data = val;
        p->next = NULL;
    }
    return p;
}

node_t *link_insert1(node_t *head, int val)
{
    node_t *insertp = make_node(val);
    node_t *tail;

    if(insertp == NULL || head == NULL){
        if(head == NULL){
            head = insertp;
        }
        return head;
    }
    for(tail = head; tail->next; tail = tail->next)
        ;
    tail->next = insertp;
    return head;
}

node_t *link_insert2(node_t *head, int val)
{
    node_t *insertp = make_node(val);

    if(insertp == NULL && head != NULL){
        return head;
    }
    insertp->next = head;
    head = insertp;
    return head;
}

node_t *link_insert3(node_t *head, int val)
{
    node_t *insertp = make_node(val), *pre, *cur;
    
    if(insertp == NULL || head == NULL){
        if(head == NULL)
            head = insertp;
        return head;
    }
    for(pre = cur = head; cur && cur->data < val; pre = cur, cur = cur->next)    
        ;
    if(cur == head){
        insertp->next = head;
        head = insertp;
    }else{
        pre->next = insertp;
        insertp->next = cur;
    }
    return head;
}

void link_print(node_t *head)
{
    node_t *cur;

    for(cur = head; cur; cur = cur->next)
        printf("--%d--\n", cur->data);
}

void link_destroy(node_t *head)
{
    node_t *cur, *next;

    for(cur = head; cur; cur = next){
        next = cur->next;
        free(cur);
    }
}

node_t *link_remove(node_t *head, int val)
{
    node_t *rmp = NULL, *pre, *cur;
    if(head == NULL)
        return NULL;
    if(head->data == val){
        rmp = head;
        head = head->next;
        return rmp;
    }
    for(pre = head, cur = head->next; cur; pre = pre->next, cur = cur->next){
        if(cur->data == val){
            rmp = cur;
            pre->next = cur->next;
            rmp->next = NULL;
            return rmp;
        }
    }
    return NULL;
}

int main(void)
{
    int n;
    node_t *head = NULL, *rmp;

    while(1){
        scanf("%d", &n);
        if(n == 0)
            break;
        head = link_insert3(head, n);
    }

    rmp = link_remove(head, 3);
    link_print(head);
    link_destroy(head);
    return 0;
}
