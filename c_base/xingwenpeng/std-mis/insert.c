#include <stdio.h>
#include <stdlib.h>
#include "common.h"

static void writetofile(char *filename, link_t head);

link_t insertrecord(char *filename, link_t head)
{
	link_t newrecord = (link_t)malloc(sizeof(node_t));
	link_t pre;
	int ID = 0;

	printf("Please input the new info(name chgrade mathgrade):\n");
	while(1)
	{
        for(pre = head; pre->next != NULL; pre = pre->next)
		{
			ID = pre->ID;
		}
		if(3 != scanf("%s %4f %4f", newrecord->name, &newrecord->chgrade, &newrecord->mathgrade))
		{
			printf("Please input again!\n");
			continue;
		}
        newrecord->ID = ID + 2;
        newrecord->average = (newrecord->chgrade + newrecord->mathgrade) / 2.0;
		newrecord->next = NULL;
		break;
	}
	if(head == NULL)
		head = newrecord;
	else
		pre->next = newrecord;

	writetofile(filename, head);
	return head;
}

static void writetofile(char *filename, link_t head)
{
	FILE *fp;
	link_t tmp = head;
	fp = openfile(filename, 4);
	while(tmp)
	{
		fprintf(fp, "%d %s %4.1f %4.1f\n", tmp->ID, tmp->name, tmp->chgrade, tmp->mathgrade);
		tmp = tmp->next;
	}

	closefile(fp);
}
