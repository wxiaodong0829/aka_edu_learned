/*************************************************************************
    > File Name: sort.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月09日 星期四 18时51分35秒
 ************************************************************************/
#include "link.h"
//-------------------------------------------------
//
//		sort 排序
//
//-------------------------------------------------
int cmp_id(const void *a, const void *b)
{
	return (*(node_t **)a)->id - (*(node_t **)b)->id;
}
int cmp_name(const void *a, const void *b)
{
	return strcmp((*(node_t **)a)->name, (*(node_t **)b)->name);
}
int cmp_chgrade(const void *a, const void *b)
{
	return ((*(node_t **)a)->chgrade - (*(node_t **)b)->chgrade);
}
int cmp_mathgrade(const void *a, const void *b)
{
	return ((*(node_t **)a)->mathgrade - (*(node_t **)b)->mathgrade);
}
int cmp_average(const void *a, const void *b)
{
	return ((*(node_t **)a)->average - (*(node_t **)b)->average);
}

node_t *link_sort_do(node_t *head, int(*cmp)(const void *a, const void *b))
{
	int len, i;
	node_t *p, *q;
	if (head == NULL) {
		printf("this list is NULL");
		return NULL;
	}
	for (p = head->next, len = 0; p; len++, p = p->next)
		;
	node_t **s;
	s = malloc(sizeof(*s) * (len + 1));
	memset(s, (int)NULL, sizeof(*s) * (len + 1));
	for (p = head->next, i = 0; p; p = p->next) {
		s[i] = p;
	//	printf("\ndebug:%p :", s[i]);
		i++;
	}
	s[i] = NULL;
	//printf("\ndebug:%p :", s[i]);
	qsort(s, len, sizeof(*s), cmp);
	/*-----------------------------------------------
	      god  it !!
	-----------------------------------------------*/
	for (p = head, i = 0; p->next = s[i]; p = p->next, i++) 
		;
		
	return head;
}
