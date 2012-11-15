/*************************************************************************
    > File Name: reverser.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月11日 星期六 15时26分04秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int num;
	struct node * next;
}node_t;
node_t *NODE(int num, node_t *next)
{
	node_t *p = malloc(sizeof(*p));
	p->num = num;
	p->next = next;
	return p;
}
void init_head(node_t **head)
{
	*head = NODE(0, NULL);
}
node_t * link_insert_one_b(node_t *head, int num)
{
	if (head == NULL) {
		puts("error: link_insert_one_b head is NULL");
		return NULL;
	}
	node_t *p = NODE(num, NULL);

	p->next = head->next;
	head->next = p;
	return head;
}
void link_print(node_t *head)
{
	node_t *p;
	for (p = head->next; p; p = p->next)
		printf("%4d", p->num);
	printf("\n");
}
node_t * link_reverse(node_t *head)
{
	node_t  *pnext = NULL;
	node_t * p = head->next->next;
	head->next->next = NULL;
	for (; p; p = pnext) {
		pnext = p->next;
		p->next = head->next;
		head->next = p;
	}
	return head;
}
int main(void)
{
	int len = 0, i;
	node_t str[3] = {{1, NULL}, {2, NULL}, {3, NULL}};

	node_t *link_head = NULL;
	init_head(&link_head);
	len = sizeof(str)/sizeof(str[0]);

	for (i = 0; i < len; i++) {
		if ((link_head = link_insert_one_b(link_head, str[i].num)) == NULL) {
			puts("error: main at link_insert_one_b");
			exit(-1);
		}
	}
	link_print(link_head);
//printf("asdf\n");
	if ((link_head = link_reverse(link_head)) == NULL) {
		puts("error: main at link_insert_one_b");
		exit(-1);
	}
	link_print(link_head);
	return 0;
}
