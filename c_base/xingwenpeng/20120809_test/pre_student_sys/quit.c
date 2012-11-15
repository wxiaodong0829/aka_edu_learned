/*************************************************************************
    > File Name: quit.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com > 自由  谐作   创造   沟通 > Created Time: 2012年08月08日 星期三 16时33分28秒
 ************************************************************************/

#include "link.h"
#include <stdlib.h>
void link_destroy(node_t **head)
{
	node_t *current, *tmp;
	for (current = *head; current; current = tmp) {
		tmp = current->next;
		free(current);
	}
	*head = NULL;
}

void link_fclose(FILE *fp)
{
	fclose(fp);
}


