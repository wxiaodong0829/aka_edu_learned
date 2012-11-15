/*************************************************************************
    > File Name: double_head_link.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月07日 星期二 16时24分20秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "double_head_link.h"

#if 0
typedef struct node {
	int val;
	struct node *pre;
	struct node *next;
}node_t;
//初始化
void link_head_init(node_t **head);
//增
node_t *link_insert_e_next(node_t *head, int val);
node_t *link_insert_b_next(node_t *head, int val);
//删
node_t *link_remove_pre(node_t *end, int key);
node_t *link_remove_next(node_t *head, int key);
	//释放
void link_node_free(node_t *p);
//查 （改）
node_t *link_search_next(node_t *head, int key);
node_t *link_search_pre(node_t *end, int key);
//遍历显示
char * link_print_pre(node_t *end);
void link_print_next(node_t *head);
//销毁 链表
void link_destroy(node_t **head);
node_t * NODE(int val, node_t *pre, node_t *next);
#endif
node_t * NODE(int val, node_t *pre, node_t *next)
{
	node_t *p = malloc(sizeof *p);
	p->val = val;
	p->pre = pre;
	p->next = next;
	return p;
}

void link_head_init(node_t **head)
{
	*head = NODE(0, NULL, NULL);	//有一个空表头
}
/* 用next 指针 实现 尾插法
 *
 */
node_t *link_insert_e_next(node_t *head, int val)
{
	node_t  *insert, *current;
	insert = NODE(val, NULL, NULL);
	if (insert == NULL) {
		printf("link_insert_e fail \n");
		return NULL;
	}

	// 核心语句----------
	for (current = head; current->next; current = current->next)
		;
	current->next = insert;
	insert->pre = current;
	//-------------------

	return head;
}
/* 用next 指针 实现 头插法
 */
node_t *link_insert_b_next(node_t *head, int val)
{
	node_t  *insert;
	insert = NODE(val, NULL, NULL);
	if (insert == NULL) {
		printf("link_insert_b fail \n");
		return NULL;
	}

	if (head == NULL) {
		head = insert;
		return head;
	}
	// 核心语句----------
	insert->next = head->next;
	head->next = insert;

	insert->next->pre = insert;
	insert->pre = head;
	//-------------------

	return head;
}
char * link_print_pre(node_t *end)
{
	node_t *p;
	if (end == NULL) {
		printf("end of the point is NULL");
		return NULL;
	}
	printf("%d\n", end->val);
	for (p = end->pre; p->pre; p = p->pre)
		printf("%d\n", p->val);
	return (char *)1;
}
void link_print_next(node_t *head)
{
	node_t *p;
	for (p = head->next; p; p = p->next)
		printf("%d\n", p->val);
}
node_t *link_search_pre(node_t *end, int key)
{
	node_t *p;
	for (p = end; p->pre; p = p->pre) {
		if (key == p->val)
			return p;
	}
	return NULL;
}
node_t *link_search_next(node_t *head, int key)
{
	node_t *p;
	for (p = head->next; p; p = p->next) {
		if (key == p->val)
			return p;
	}
	return NULL;
}
node_t *link_remove_pre(node_t *end, int key)
{
	node_t *p, *q;
	if (end== NULL)
		return NULL;
	//只有最后一个元素
	if (end->val == key) {
			p = end->pre;
			p->next = NULL;
			end->pre = NULL;
			return end;
	}
	if (end->pre == NULL)
	//只有最后一个元素
			return NULL;

	for (q = end, p = end->pre; p; q = q->pre, p = p->pre) {
		if (p->val == key) {
			q->pre = p->pre;
			p->pre->next = q;

			p->pre = p->next = NULL;
			return p;
		}
	}
	return NULL;
}
//只是把这个结构体取下来，并不释放空间
node_t *link_remove_next(node_t *head, int key)
{
	node_t *p, *q;
	if (head == NULL)
		return NULL;
	for (q = head, p = head->next; p; q = q->next, p = p->next) {
		if (p->val == key) {
			q->next = p->next;
			p->next->pre = q;

			p->next = p->pre = NULL;
			return p;
		}
	}
	return NULL;
}
void link_node_free(node_t *p)
{
	free(p);
}
// 传 指针的指针 方便对头指针去野指针化 (野指针：指向一个堆中已释放的地址或其它未分配的地址，或没有读写属性的地址)
void link_destroy(node_t **head)
{
	node_t *current, *tmp;
	for (current = *head; current; current = tmp) {
		tmp = current->next;
		free(current);
	}
	*head = NULL;
}
#ifdef DEBUG
int main(void)
{
	node_t *link_head = NULL;
	link_head_init(&link_head);

	int a[5] = {1, 2, 3, 4, 5};
	int i;
	node_t *tmp = NULL;
	for (i = 0; i < 5; i++) 
		link_head = link_insert_e_next(link_head, a[i]);

	for (tmp = link_head; tmp->next; tmp = tmp->next)
		;
	link_print_pre(tmp);
	//tmp = link_search_pre(tmp, 1);
	//移除元素是 3 的结构体
	tmp = link_remove_pre(tmp, 3);
	//printf("\n%d\n", tmp->val);
	//释放元素是 3 的结构体
	link_node_free(tmp);

	//销毁此链表，释放所有空间
	link_destroy(&link_head);
#if 0
	//tmp = link_search_next(link_head, 4);
	printf("\n%d\n", tmp->val);
	//移除元素是 3 的结构体
	tmp = link_remove_next(link_head, 3);
	//释放元素是 3 的结构体
	link_node_free(tmp);

	//销毁此链表，释放所有空间
	link_destroy(&link_head);
#endif 
	return 0;
}
#endif
