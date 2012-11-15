/*************************************************************************
    > File Name: demo_link.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月12日 星期日 16时42分30秒
 ************************************************************************/

#include <stdio.h>

struct node
{
	int id;
	char name[8];
	struct node *nbext;	
};

node_t *serach(node_t *head, void *ptr, handler_t handler)
{

}
