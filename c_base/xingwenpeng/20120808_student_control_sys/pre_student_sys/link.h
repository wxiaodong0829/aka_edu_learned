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

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define LEN 20

typedef struct node {
	char c;
	int val;
	char s[LEN];
	struct node *next;
}node_t;
//初始化
node_t * NODE(char c, int val, char *s, node_t *next);
void init_head(node_t **link_head);
//读取文件内容到内存
FILE *link_read_file(const char * filename, node_t **head);
//增
node_t *link_insert_b(char *s, node_t *head);
//删 移除
node_t *link_remove(node_t *head, int key);
node_t *link_remove_charchar(node_t *head, void *ptr);
node_t *link_remove_char(node_t *head, void *ptr);
node_t *link_remove_int(node_t *head, void *ptr);
	//释放
void link_node_free(node_t *p);
//查 改
node_t *link_search(node_t *head, int key);
node_t *link_search_charchar(node_t *head, void * key);
node_t *link_search_char(node_t *head, void *key);
node_t *link_search_int(node_t *head, void *key);
//遍历显示
void link_print(node_t *head);
//销毁 链表
void link_destroy(node_t **head);
//从文件中读取信息
node_t * read_from_in(FILE *fp, node_t *head);
//关闭文件
void link_fclose(FILE *fp);

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
			case (offsetof(type, c)) :\
				ret = link_search_char(head, (void *)ptr);\
				break;\
			case (offsetof(type, val)) :\
				ret = link_search_int(head, (void *)ptr);\
				break;\
			case (offsetof(type, s)) :\
				ret = link_search_charchar(head, (void *)ptr);\
				break;\
			default:\
				break;\
		}\
	}while(0)

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
			case (offsetof(type, c)) :\
				ret = link_remove_char(head, (void *)ptr);\
				break;\
			case (offsetof(type, val)) :\
				ret = link_remove_int(head, (void *)ptr);\
				break;\
			case (offsetof(type, s)) :\
				ret = link_remove_charchar(head, (void *)ptr);\
				break;\
			default:\
				break;\
		}\
	}while(0)

#endif
