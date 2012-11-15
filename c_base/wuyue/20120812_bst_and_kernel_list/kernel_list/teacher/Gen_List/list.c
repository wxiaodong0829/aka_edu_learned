#include <stdio.h>
#include <stdlib.h>

struct list_node
{
	struct list_node *next;
};
typedef struct list_node node_t;
typedef void *(*handler_t)(void *);

#define INIT_NODE(ptr) \
	do{ \
		(ptr)->next = NULL; \
	}while(0)

#define offsetof(type, mem) (int)&(((type *)0)->mem)

#define containerof(ptr, type, mem) \
	(type *)((char *)ptr - offsetof(type, mem))

#define LIST_TRAVAL(head, type, handler) \
	do{ \
		node_t *p, *q; \
		for(p = head; p != NULL; p = q){ \
			q = p->next; \
			handler((void *)containerof(p, typeof(type), list)); \
		} \
	}while(0)

int list_insert(node_t **head, node_t *new)
{
	node_t *p;

	if(*head == NULL){
		*head = new;
		return 0;
	}
	p = *head;
	while(p->next != NULL)
		p = p->next;
	p->next = new;

	return 0;
}

int list_remove(node_t **head, node_t *item)
{
	node_t *p, *q;

	if(*head == NULL)
		return -1;
	if(*head == item){
		*head = item->next;
		item->next = NULL;
		return 0;
	}
	q = *head; p = q->next;
	while(p != NULL){
		if(p == item){
			q->next = p->next;
			p->next = NULL;
			return 0;
		}
		p = p->next; q = q->next;
	}

	return -1;
}

/************test code**************/
#ifdef DEBUG
typedef struct
{
	int val;
	node_t list;	
}int_node_t;

int_node_t *new_node(int val)
{
	int_node_t *p;

	p = (int_node_t *)malloc(sizeof(*p));
	if(p == NULL)
		return NULL;
	p->val = val;
	INIT_NODE(&(p->list));

	return p;
}

void print_node(void *arg)
{
	int_node_t *p;

	p = (int_node_t *)arg;
	printf("%d\n", p->val);
}

void free_node(void *arg)
{
	free(arg);
}

int main(void)
{
	int n;
	int_node_t *p;
	node_t *head = NULL;

	while(1){
		scanf("%d", &n);
		if(n == -1)
			break;
		p = new_node(n);
		list_insert(&head, &p->list);
	}

	LIST_TRAVAL(head, int_node_t, print_node);
	
	LIST_TRAVAL(head, int_node_t, free_node);
	head = NULL;

	return 0;
}
#endif
