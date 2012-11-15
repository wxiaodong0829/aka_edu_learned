/*************************************************************************
    > File Name: link.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月08日 星期三 16时02分58秒
 ************************************************************************/

#ifndef _LINK_H 
#define _LINK_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define LEN 20

#define id_opera  p->id == *(int *)ptr
#define name_opera  (strcmp(p->name, ((char *)ptr)) == 0)
#define chgrade_opera  p->chgrade == *(float *)ptr
#define mathgrade_opera  p->mathgrade == *(float *)ptr
#define average_opera  p->average == *(float *)ptr

typedef struct node {
	int id;
	char *name[LEN];
	float chgrade;
	float mathgrade;
	float average;
	struct node *next;
}node_t;
//-------------------------------------------------
//
//----------------------初始化----------------------
//
//
//-------------------------------------------------
node_t * NODE(int id, char *name, float chgrade, float mathgrade, float average, node_t *next);

void init_head(node_t **link_head);
//-------------------------------------------------
//
//				读取文件内容到内存
//
//
//-------------------------------------------------
FILE *link_read_file(const char * filename, node_t **head);
node_t * read_from_in(FILE *fp, node_t *head);
//-------------------------------------------------
//
//			增加一行字符信息(一个结构体)到内存的链表
//
//
//-------------------------------------------------
//
node_t *link_insert_b(char *s, node_t *head);
//
//-------------------------------------------------
//
//删 移除
//
//
//-------------------------------------------------

#define link_remove_memb(member) \
node_t *link_remove_##member(node_t *head, void *ptr)\
{\
	node_t *p, *q;\
	if (head == NULL)\
		return NULL;\
\
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
/*
 *remove a struct node ,depends its member member and it's point
 * ptr  :	member's point
 * type	:	the struct types
 *member:	depends on
 *head	:	the head of list link_head
 *ret	:	return the sub_remove value
 *
 */
#define link_remove(ptr, type, member, head, ret) do {\
		switch ((offsetof (type, member))) {\
			case (offsetof(type, id)) :\
				ret = link_remove_id(head, (void *)ptr);\
				break;\
			case (offsetof(type, name)) :\
				ret = link_remove_name(head, (void *)ptr);\
				break;\
			case (offsetof(type, chgrade)) :\
				ret = link_remove_chgrade(head, (void *)ptr);\
				break;\
			case (offsetof(type, mathgrade)) :\
				ret = link_remove_mathgrade(head, (void *)ptr);\
				break;\
			case (offsetof(type, average)) :\
				ret = link_remove_average(head, (void *)ptr);\
				break;\
			default:\
				break;\
		}\
	}while(0)


//
//
	//释放
//
//
//-------------------------------------------------
void link_node_free(node_t *p)
{
	free(p);
}
//
//-------------------------------------------------
//
//查 改
//
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
link_search_memb(name
link_search_memb(chgrade)
link_search_memb(mathgrade)
link_search_memb(average)
/*
 *search a struct node ,depends its member member and it's point
 * ptr  :	member's point
 * type	:	the struct types
 *member:	depends on
 *head	:	the head of list link_head
 *ret	:	return the sub_remove value
 *
 */
#define link_search(ptr, type, member, head, ret) do {\
		switch ((offsetof (type, member))) {\
			case (offsetof(type, id)) :\
				ret = link_search_id(head, (void *)ptr);\
				break;\
			case (offsetof(type, name)) :\
				ret = link_search_name(head, (void *)ptr);\
				break;\
			case (offsetof(type, chgrade)) :\
				ret = link_search_chgrade(head, (void *)ptr);\
				break;\
			case (offsetof(type, mathgrade)) :\
				ret = link_search_mathgrade(head, (void *)ptr);\
				break;\
			case (offsetof(type, average)) :\
				ret = link_search_average(head, (void *)ptr);\
				break;\
			default:\
				break;\
		}\
	}while(0)

//
//-------------------------------------------------
//
//遍历显示
//
//
//-------------------------------------------------
void link_print(node_t *head);
//
//-------------------------------------------------
//
//销毁 链表
//
//
//-------------------------------------------------
void link_destroy(node_t **head);
//
//-------------------------------------------------
//
//关闭文件
//
//
//-------------------------------------------------
void link_fclose(FILE *fp);


#endif
