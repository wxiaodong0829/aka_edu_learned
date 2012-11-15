/*************************************************************************
    > File Name: search.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月08日 星期三 16时31分00秒
 ************************************************************************/

#include "link.h"
#include <string.h>

void link_print(node_t *head)
{
	node_t *p;
	for (p = head->next; p; p = p->next) {
		printf("%c ", p->c);
		printf("%d ", p->val);
		printf("%s \n", p->s);

	}
}


node_t *link_search_charchar(node_t *head, void * key)
{
	node_t *p;
	for (p = head->next; p; p = p->next) {
		if (strcmp(p->s, *(char **)key) == 0)
			return p;
	}
	return NULL;
}

node_t *link_search_char(node_t *head, void *key)
{
	node_t *p;
	for (p = head->next; p; p = p->next) {
		if (*(char *)key == p->c)
			return p;
	}
	return NULL;
}

node_t *link_search_int(node_t *head, void *key)
{
	node_t *p;
	for (p = head->next; p; p = p->next) {
		if (*(int *)key == p->val)
			return p;
	}
	return NULL;
}

