/*************************************************************************
    > File Name: init.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月08日 星期三 16时08分00秒
 ************************************************************************/
#include "link.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

node_t * NODE(int id, char *name, float chgrade, float mathgrade, float average, node_t *next)
{
	node_t *p = malloc(sizeof(*p));
	p->id = id;
	strcpy(p->name, name);
	p->chgrade = chgrade;
	p->mathgrade= mathgrade;
	p->average= average;
	p->next = next;
	return p;
}
void init_head(node_t **link_head)
{
	if ((*link_head = NODE(0, " ", 0.0, 0.0, 0.0, NULL)) == NULL) {
		printf("init_head fail\n");
		exit(-1);
	}
}

