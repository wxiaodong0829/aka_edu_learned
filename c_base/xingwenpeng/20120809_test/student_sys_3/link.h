/*************************************************************************
    > File Name: link.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月08日 星期三 16时02分58秒
 ************************************************************************/

#ifndef _LINK__H 
#define _LINK__H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define LEN 20

typedef struct node {
	int id;
	char name[LEN];
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
node_t *link_remove_id(node_t *head, void *ptr);
node_t *link_remove_name(node_t *head, void *ptr);
node_t *link_remove_chgrade(node_t *head, void *ptr);
node_t *link_remove_mathgrade(node_t *head, void *ptr);
node_t *link_remove_average(node_t *head, void *ptr);
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
//
//				查 改
//
//
//-------------------------------------------------

node_t * link_search_id(node_t *head, void *ptr);
node_t * link_search_name(node_t *head, void *ptr);
node_t * link_search_chgrade(node_t *head, void *ptr);
node_t * link_search_mathgrade(node_t *head, void *ptr);
node_t * link_search_average(node_t *head, void *ptr);
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
		switch ((offsetof(type, member))) {\
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

//-------------------------------------------------
//
//		sort 排序
//
//
//-------------------------------------------------
int cmp_id(const void *a, const void *b);
int cmp_name(const void *a, const void *b);
int cmp_chgrade(const void *a, const void *b);
int cmp_mathgrade(const void *a, const void *b);
int cmp_average(const void *a, const void *b);

node_t *link_sort_do(node_t *head, int(*cmp)(const void *, const void *));

#define link_sort(head, type, member, ret) do {\
		switch ((offsetof(type, member))) {\
			case (offsetof(type, id)) :\
				ret = link_sort_do(head, cmp_id);\
				break;\
			case (offsetof(type, name)) :\
				ret = link_sort_do(head, cmp_name);\
				break;\
			case (offsetof(type, chgrade)) :\
				ret = link_sort_do(head, cmp_chgrade);\
				break;\
			case (offsetof(type, mathgrade)) :\
				ret = link_sort_do(head, cmp_mathgrade);\
				break;\
			case (offsetof(type, average)) :\
				ret = link_sort_do(head, cmp_average);\
				break;\
			default:\
				break;\
		}\
	}while(0)

//-------------------------------------------------
//void link_node_free(node_t *p);
//{
//	free(p);
//}
///
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
