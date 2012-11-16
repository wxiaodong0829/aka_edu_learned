#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    int a; int b;
}res_t;
void *tfn(void *arg)
{
    res_t *p;
    p = (res_t *)malloc(sizeof(res_t));
    p->a = 100, p->b = 200;
    return (void *)p;
}
int main(void)
{
    pthread_t tid; res_t *q;
    pthread_create(&tid, NULL, tfn, NULL);
    pthread_join(tid, (void **)&q);
    printf("%d, %d\n", q->a, q->b);

    return 0;
}
