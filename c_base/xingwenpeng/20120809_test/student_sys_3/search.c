/*************************************************************************
    > File Name: search.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月09日 星期四 16时10分56秒
 ************************************************************************/

#include "link.h"

#define id_opera  p->id == *(int *)ptr
#define name_opera  (strcmp(p->name, (char *)ptr) == 0)
#define chgrade_opera  p->chgrade == *(float *)ptr
#define mathgrade_opera  p->mathgrade == *(float *)ptr
#define average_opera  p->average == *(float *)ptr

//-------------------------------------------------
//
//			查 改
//
//-------------------------------------------------
#define link_search_memb(member)  \
node_t *link_search_##member(node_t *head, void * ptr)\
{\
	node_t *p;\
	for (p = head->next; p; p = p->next) {\
		if (member##_opera)\
			return p;\
	}\
	return NULL;\
}
link_search_memb(id)
link_search_memb(name)
link_search_memb(chgrade)
link_search_memb(mathgrade)
link_search_memb(average)

