#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define MAXCHAR 200
static link_t mk_node(node_t std)
{
		link_t p = malloc(sizeof(node_t));
        std.average = (std.chgrade + std.mathgrade) / 2.0;
        

        if(p != NULL){
            *p = std;
            p->next = NULL;
        }
		return p;
}

link_t creat(char *name, int flagbyaverage, link_t head)
{
	FILE *fp;
	link_t cur, tmp, pre, tail;
    node_t std;

	fp = openfile(name, 1);
    while(EOF != fscanf(fp, "%u %s %4f %4f\n", &std.ID, std.name, &std.chgrade, &std.mathgrade)){
        tmp = mk_node(std);

        if(head == NULL || tmp == NULL){
            if(head == NULL)
                head = pre = tail = tmp;
        }else if(!flagbyaverage){
            tail->next = tmp;
            tail = tmp;
        }else{
            for(pre = cur = head; cur && (tmp->average > cur->average); ){
                pre = cur;
                cur = cur->next;
            }                 
            if(pre == head && cur == head){
                tmp->next = head;
                head = tmp;
            }else{
                pre->next = tmp;
                tmp->next = cur;
            }
        }
    }
	closefile(fp);
    return head;
}

void link_destroy(link_t head)
{
    link_t cur, next;

    for(cur = head; cur != NULL; cur = next){
        next = cur->next;
        free(cur);
    }
}
