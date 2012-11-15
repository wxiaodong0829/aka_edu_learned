#include <stdio.h>

typedef struct node {
	int val;
	struct node *next;
}node_t;

node_t *link_head = NULL;
node_t *make_node(int val)
{
	node_t *p = (node_t *)malloc(sizeof(node_t));
	if (p == NULL) {
		perror("malloc");
		return NULL
	}
	p->val = val;
	p->next = NULL;
	return p;
}
/* link end insert */
node_t *link_insert_e(node_t *head, int val)
{
	node_t *p, *q;
	p = make_node(val);	
	if (p == NULL) {
		printf("link_insert_e fail\n");
		return NULL;
	}
	if (head == NULL) {	
		head = p;
		return head;	
	}
	for (q = head; q->next != NULL; q = q->next)	
		;
	q->next = p;
	
	return head;	
}
node_t *link_insert_b(node_t *head, int val)
{
	node_t *p;
	p = make_node(val);
	if (p == NULL) {
		printf("link_insert_e fail\n");
		return NULL;
	}
	if (head == NULL) {
		head = p;
		return head;
	}
	p->next = head->next;
	head->next = p;
	return head;
}
