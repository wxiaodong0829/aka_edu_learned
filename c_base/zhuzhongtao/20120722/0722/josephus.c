#include <stdio.h>
#include <stdlib.h>
#define N 41
#define M 3
typedef struct node *link;
struct node { int item; link next; };
link NODE(int item, link next)
{
    link t = malloc(sizeof *t);
    t->item = item;
    t->next = next;
    return t;
}
int main()
{
    int i;
    link t = NODE(1, NULL); t->next = t;
    for (i=2; i<=N; i++) t = t->next = NODE(i, t->next);
    while (t!=t->next) {
        for (i=1; i<M; i++) t = t->next;
        t->next = t->next->next;
    }
    printf("%d\n", t->item);
    return 0;
}
