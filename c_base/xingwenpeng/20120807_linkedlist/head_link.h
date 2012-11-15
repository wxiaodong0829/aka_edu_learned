/*************************************************************************
    > File Name: head_link.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月08日 星期三 08时39分17秒
 ************************************************************************/
#ifndef _HEAD_LINK_H
#define _HEAD_LINK_H

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
