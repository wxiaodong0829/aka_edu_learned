/*************************************************************************
    > File Name: head_link.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月07日 星期二 16时24分20秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "head_link.h"

#if 0
typedef struct node {
	int val;
	struct node *next;
}node_t;
//初始化
void link_head_init(node_t **head);
//增
node_t *link_insert_e(node_t *head, int val);
node_t *link_insert_b(node_t *head, int val);
//删 (移除)
node_t *link_remove(node_t *head, int key);
	//释放
void link_node_free(node_t *p);
//查 （改）
node_t *link_search(node_t *head, int key);
//遍历显示
void link_print(node_t *head);
//销毁 链表
void link_destroy(node_t **head);
node_t * NODE(int val, node_t *next);
#endif
node_t * NODE(int val, node_t *next)
{
	node_t *p = malloc(sizeof *p);
	p->val = val;
	p->next = next;
	return p;
}

void link_head_init(node_t **head)
{
	*head = NODE(0, NULL);	//有一个空表头
}
/* 尾插法
 *
 */
node_t *link_insert_e(node_t *head, int val)
{
	node_t  *insert, *current;
	insert = NODE(val, NULL);
	if (insert == NULL) {
		printf("link_insert_e fail \n");
		return NULL;
	}

	// 核心语句----------
	for (current = head; current->next; current = current->next)
		;
	current->next = insert;
	//-------------------

	return head;
}
/* 头插法
 */
node_t *link_insert_b(node_t *head, int val)
{
	node_t  *insert;
	insert = NODE(val, NULL);
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
	//-------------------

	return head;
}
void link_print(node_t *head)
{
	node_t *p;
	for (p = head->next; p; p = p->next)
		printf("%d\n", p->val);
}
node_t *link_search(node_t *head, int key)
{
	node_t *p;
	for (p = head->next; p; p = p->next) {
		if (key == p->val)
			return p;
	}
	return NULL;
}
//只是把这个结构体取下来，并不释放空间
node_t *link_remove(node_t *head, int key)
{
	node_t *p, *q;
	if (head == NULL)
		return NULL;
	for (q = head, p = head->next; p; q = q->next, p = p->next) {
		if (p->val == key) {
			q->next = p->next;
			p->next = NULL;
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
		link_head = link_insert_e(link_head, a[i]);
	link_print(link_head);
	tmp = link_search(link_head, 4);
	printf("\n%d\n", tmp->val);
	//移除元素是 3 的结构体
	tmp = link_remove(link_head, 3);
	//释放元素是 3 的结构体
	link_node_free(tmp);

	//销毁此链表，释放所有空间
	link_destroy(&link_head);
	return 0;
}
#endif
