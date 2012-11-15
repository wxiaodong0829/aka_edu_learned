#include <stdio.h>
#include <stdlib.h>

typedef struct node *link_t;

typedef struct node{
    unsigned char item;
    link_t prev, next;
}node_t;

node_t tailsentinel;
node_t headsentinel = {0, NULL, &tailsentinel};
node_t tailsentinel = {0, &headsentinel, NULL};


static link_t head = &headsentinel;
static link_t tail = &tailsentinel;

link_t make_node(unsigned char item)
{
    link_t p = malloc(sizeof(node_t));
    if(p != NULL){
        p->item = item;
        p->prev = p->next = NULL;
    }
    return p;
}

void free_node(link_t p)
{
    free(p);
}

link_t link_search(unsigned char key)
{
    link_t p;

    for(p = head->next; p != tail; p = p->next)
        if(p->item == key)
            return p;
    return NULL;
}

void link_insert(link_t p)
{
    p->next = head->next;
    head->next->prev = p;
    head->next = p;
    p->prev = head;
}

void link_delete(link_t p)
{
    p->prev->next = p->next;
    p->next->prev = p->prev;
}

void link_traverse(void (*visit)(link_t))
{
    link_t p;
    for(p = head->next; p!= tail; p = p->next)
        visit(p);
}

void link_destroy(void)
{
    link_t q, p = head->next;
    head->next = tail;
    tail->prev = head;
    while(p != tail){
        q = p;
        p = p->next;
        free_node(q);
    }
}

void link_print(link_t p)
{
    printf("%d\n", p->item);
}

int main(void)
{
    link_t p = make_node(10);
    link_insert(p);

    p = make_node(5);
    link_insert(p);

    p = make_node(90);
    link_insert(p);

    p = link_search(5);
    link_delete(p);
    free_node(p);
    link_traverse(link_print);

    link_destroy();
    return 0;
}
