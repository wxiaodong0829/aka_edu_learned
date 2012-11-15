#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 20
typedef struct node *link;
struct node { int item; link l, r; };
link NODE(int item, link l, link r)
{
    link t = malloc(sizeof *t);
    t->item = item; t->l = l; t->r = r;
    return t;
}
link insert_node(link t, int item)
{
    if (t==NULL) return NODE(item, NULL, NULL);
    if      (item < t->item)
        t->l = insert_node(t->l, item);
    else if (item > t->item)
        t->r = insert_node(t->r, item);
    return t;
}
void pre_ord(link t)
{
    if (t==NULL) return;
    printf("%3d", t->item);
    pre_ord(t->l);
    pre_ord(t->r);
}
void in_ord(link t)
{
    if (t==NULL) return;
    in_ord(t->l);
    printf("%3d", t->item);
    in_ord(t->r);
}
void post_ord(link t)
{
    if (t==NULL) return;
    post_ord(t->l);
    post_ord(t->r);
    printf("%3d", t->item);
}
int main()
{
    int i; link T = NULL;
    srand(time(NULL));
    for (i=0; i<N; i++) T = insert_node(T, rand()%100);
    pre_ord(T); printf("\n");
    in_ord(T); printf("\n");
    post_ord(T); printf("\n");
    return 0;
}
