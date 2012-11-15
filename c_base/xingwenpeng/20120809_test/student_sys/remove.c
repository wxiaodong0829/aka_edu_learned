/*************************************************************************
    > File Name: remove.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月09日 星期四 16时13分15秒
 ************************************************************************/

#include "link.h"

#define id_opera  p->id == *(int *)ptr
#define name_opera  (strcmp(p->name, (char *)ptr) == 0)
#define chgrade_opera  p->chgrade == *(float *)ptr
#define mathgrade_opera  p->mathgrade == *(float *)ptr
#define average_opera  p->average == *(float *)ptr
//-------------------------------------------------
//
//				删 移除
//
//-------------------------------------------------
#define link_remove_memb(member) \
node_t *link_remove_##member(node_t *head, void *ptr)\
{\
	node_t *p, *q;\
	if (head == NULL)\
		return NULL;\
	for (q = head, p = head->next; p; q = q->next, p = p->next) {\
		if (member##_opera) {\
			q->next = p->next;\
			p->next = NULL;\
			return p;\
		}\
	}\
	return NULL;\
}
link_remove_memb(id)
link_remove_memb(name)
link_remove_memb(chgrade)
link_remove_memb(mathgrade)
link_remove_memb(average)

