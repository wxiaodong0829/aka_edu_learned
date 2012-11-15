/*************************************************************************
    > File Name: double_head_link.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月08日 星期三 08时41分44秒
 ************************************************************************/

#ifndef _DOUBLE_HEAD_LINK_H_
#define _DOUBLE_HEAD_LINK_H_
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
