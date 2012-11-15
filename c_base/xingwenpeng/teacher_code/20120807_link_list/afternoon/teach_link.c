#include <stdio.h>
#include <stdlib.h>

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
		return NULL;
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

void link_print(node_t *head)
{
	node_t *p;
	for (p = head; p != NULL; p = p->next) {
		printf("%d\n", p->val);
	}
}
void link_destroy(node_t *head)
{
	node_t *p, *q;
	for (q = head; q != NULL; q = p) {
		p = q->next;
		free(q);	//难点1.注意释放的先后顺序
	}		
	//	head = NULL;无意义
	link_head = NULL;
}
node_t *link_search(node_t *head, int key)
{
	node_t *p;
	for (p = head; p != NULL; p = p->next)
		if (key == p->val)
			return p;
	return NULL;
}
node_t *link_remove(node_t *head, int key)
{
	node_t *p, *q;
	if (head == NULL) 
		return NULL;
	if (head->val == key) {
		link_head = head->next;
		return head;	
	}
	for (q = head, p = head->next; p != NULL; q = q->next, p = p->next) {
		if (p->val == key) {
			q->next = p->next;
			p->next = NULL;
			return p;
		}	
	}	
	return NULL;
}
void link_node_free(node_t *p)
{
	free(p);	
}
#ifdef DEBUG
int main(void)
{
	//	link_head_init(&link_head);

	int a[5] = {1,2,3,4,5};
	int i;
	node_t *tmp = NULL;
	for (i = 0; i < 5; i++)
		link_head = link_insert_e(link_head, a[i]);
	link_print(link_head);
	//tmp = link_search(link_head, 4);
	//printf("%d\n", tmp->val);
	tmp = link_remove(link_head, 3);
	link_node_free(tmp);
	link_print(link_head);
	link_destroy(link_head);
	return 0;
}
#endif
