/*************************************************************************
    > File Name: remove.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月08日 星期三 16时10分09秒
 ************************************************************************/

#include "link.h"
#include <string.h>

node_t *link_remove_charchar(node_t *head, void *ptr)
{
	node_t *p, *q;
	if (head == NULL)
		return NULL;

	for (q = head, p = head->next; p; q = q->next, p = p->next) {
		if (strcmp(p->s, *(char **)ptr) == 0) {
			q->next = p->next;
			p->next = NULL;
			return p;
		}
	}
	return NULL;
}
node_t *link_remove_char(node_t *head, void *ptr)
{
	node_t *p, *q;
	if (head == NULL)
		return NULL;

	for (q = head, p = head->next; p; q = q->next, p = p->next) {
		if (p->c == *(char *)ptr) {
			q->next = p->next;
			p->next = NULL;
			return p;
		}
	}
	return NULL;
}
node_t *link_remove_int(node_t *head, void *ptr)
{
	node_t *p, *q;
	if (head == NULL)
		return NULL;

	for (q = head, p = head->next; p; q = q->next, p = p->next) {
		if (p->val == *(int *)ptr) {
			q->next = p->next;
			p->next = NULL;
			return p;
		}
	}
	return NULL;
}
