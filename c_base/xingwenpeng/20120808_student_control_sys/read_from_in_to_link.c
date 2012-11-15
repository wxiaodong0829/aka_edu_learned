/*************************************************************************
    > File Name: read_from_in_to_link.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月08日 星期三 09时32分41秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define LEN 20
typedef struct node {
	char c;
	int val;
	char s[LEN];
	struct node *next;
}node_t;
#if 0
//初始化
//
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
node_t * NODE(char c, int val, char *s, node_t *next);
#endif
node_t * NODE(char c, int val, char *s, node_t *next)
{
	node_t *p = malloc(sizeof(*p));
	p->c = c;
	p->val = val;
	strcpy(p->s, s);
	p->next = next;
	return p;
}
void init_head(node_t **link_head)
{
	if ((*link_head = NODE(0, 0, " ", NULL)) == NULL) {
		printf("init_head fail\n");
		exit(-1);
	}
}
node_t *link_insert_b(char *s, node_t *head)
{
	char *tmp;
	int i;
	node_t *t = NODE(0, 0, "", NULL);
	if (t == NULL) {
		printf("link_insert_b fail \n");
		return NULL;
	}
	for (tmp = s, i = 0; tmp = strtok(tmp, " \t"); i++, tmp =NULL) {
		switch (i) {
			case 0:
				t->c = tmp[0];
				break;
			case 1:
				t->val = atoi(tmp);
				break;
			case 2:
				strcpy(t->s, tmp);
				break;
			default:
				break;
		}
	}

	t->next = head->next;
	head->next = t;
	
	return head;
}
node_t *read_from_in(FILE *fp, node_t *head)
{
	char s[BUFSIZ];
	char *tmp;
	int len = 0;
	while ((tmp = fgets(s, BUFSIZ, fp)) != NULL) {
		len = strlen(s);
		if (s[len-1]  == '\n')
			s[len-1] = '\0';
		if ((head = link_insert_b(s, head)) == NULL)
			return NULL;
	}
	return head;
	
}
void link_print(node_t *head)
{
	node_t *p;
	for (p = head->next; p; p = p->next) {
		printf("%c ", p->c);
		printf("%d ", p->val);
		printf("%s \n", p->s);

	}
}
void myfclose(FILE *fp)
{
	fclose(fp);
}

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
	init_head(&link_head);
	FILE *fp;
	if ((fp = fopen("in", "r")) == NULL) {
		perror("fopen in: ");
		exit(-1);
	}
	if ((link_head = read_from_in(fp, link_head)) == NULL) {
		printf("read_from_in  error");
		exit(-1);
	}
	link_print(link_head);
	myfclose(fp);
	link_destroy(&link_head);
#if 0	
	if ((link_head = link_sort(link_head)) == NULL) {
		printf("link_sort is error");
	}
//	link_print(link_head);
#endif
	return 0;
}
#endif
