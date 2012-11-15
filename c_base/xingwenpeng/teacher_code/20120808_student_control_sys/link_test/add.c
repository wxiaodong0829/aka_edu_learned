#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    unsigned int n;
    struct node *next;
}node_t;

node_t *creat(node_t *head, char *str)
{
    char *bkup = str;
    node_t *cur;

    while(*bkup){
        cur = malloc(sizeof(node_t));
        cur->n = *bkup - '0';
        cur->next = head;
        head = cur;

        bkup++;
    }
    return head;
}

void show(node_t *head)
{
    node_t *cur = head, *del;

    while(cur){
        printf("%d ", cur->n);
        cur = cur->next;
    }
    printf("\n");
}

node_t *add(node_t *head1, node_t *head2, node_t *head)
{
    node_t *cur, *cur1 = head1, *cur2 = head2;
    int oldcarry = 0, sum = 0;

    show(head1);
    while(cur1 || oldcarry){
        if(cur1){
            sum = cur1->n + cur2->n;
            cur1 = cur1->next, cur2 = cur2->next;
        }
        sum += oldcarry;

        printf("sum = %d, oldcarry = %d\n", sum, oldcarry);
        cur = malloc(sizeof(node_t));
        if(sum >= 10){
            cur->n = sum - 10;
            oldcarry = 1;
        }else{
            cur->n = sum;
            oldcarry = 0;
        }
        sum = 0;

        cur->next = head;
        head = cur;
    }
    return head;
}

int main(int argc, char *argv[])
{
    node_t *head1 = NULL, *head2 = NULL, *head = NULL;

    head1 = creat(head1, argv[1]);
    head2 = creat(head2, argv[2]);

    show(head1);
    show(head2);

    head = add(head1, head2, head);
    show(head);
    return 0;
}
