/*************************************************************************
    > File Name: print_input.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月09日 星期四 11时24分13秒
 ************************************************************************/

#include <stdio.h>
#include "link.h"
void link_print(node_t *head)
{
	node_t *p;
	for (p = head->next; p; p = p->next) {
		printf("%d ", p->id);
		printf("%s ", p->name);
		printf("%.1f ", p->chgrade);
		printf("%.1f ", p->mathgrade);
		printf("%.1f \n", p->average);

	}
}

