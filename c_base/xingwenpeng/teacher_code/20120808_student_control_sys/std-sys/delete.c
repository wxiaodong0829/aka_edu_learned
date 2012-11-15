#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

static void showinfo(void);
static link_t deletebyID(link_t head, int *flag);
static link_t deletebyname(link_t head, int *flag);
static void writetofile(char *filename, link_t head);

link_t deleterecord(char *filename, link_t head)
{
	int selnum;
	int flag = 0;
	showinfo();
	scanf("%d", &selnum);
	switch(selnum)
	{
		case 1: flag = 0;
				head = deletebyID(head, &flag);
				break;
		case 2: flag = 0;
				head = deletebyname(head, &flag);
				break;
		case 3: 
		default:
				break;
	}
	if(flag)
		writetofile(filename, head);
	return head;
	
}

static void showinfo(void)
{
	printf("Please choose the way:\n1.Delete by ID\n2.Delete by name\n3.Exit\n");
	printf("Your choice:");
}

static link_t deletebyID(link_t head, int *flag)
{
	link_t cur, mp, pre;
	int num = 0, selnum, mpid;

    for(cur = head; cur != NULL; cur = cur->next)
		num++;

	while(1)
	{
		printf("Your should choose the number included 1-%d:", num);
		scanf("%d", &selnum);
		printf("selnum = %d\n", selnum);
		if(selnum > num || selnum < 1)
			continue;

		*flag = 1;
		for(pre = cur = head; cur->ID < selnum;){
			pre = cur;
			cur = cur->next;
		}

		if(cur == head)	{
			mp = head = head->next;
		}else{
			mp = pre->next = cur->next;
		}
		mpid = cur->ID;
		free(cur);

		while(mp){
			mp->ID = mpid;
			mp = mp->next;
			mpid++;
		}
		return head;
	}
}

static link_t deletebyname(link_t head, int *flag)
{
	char name[20];
	link_t tmp, cur, mp;
	int mpid;

	tmp = cur = head;
	printf("Please input the name which you want to delete:");
	scanf("%s", name);

	while(cur){
		while(cur){
			if(!strcmp(cur->name, name)){
				break;
			}
			tmp = cur;
			cur = cur->next;
		}
	    if(!cur){
		    printf("The name:%s which you would delete is not existed.\n", name);
		    return head;
    	}
	    *flag = 1;
	    if(cur == head){
		    mp = head = head->next;
	    }else{
		    mp = tmp->next = cur->next;
	    }
	    mpid = cur->ID;
	    while(mp){
		    mp->ID = mpid;
		    mp = mp->next;
		    mpid++;
	    }
	
	    free(cur);
	    cur = tmp;
	}
	return head;
}

static void writetofile(char *filename, link_t head)
{
	FILE *fp;
	link_t tmp = head;
	fp = openfile(filename, 4);
	while(tmp){
		fprintf(fp, "%d %s %4.1f %4.1f\n", tmp->ID, tmp->name, tmp->chgrade, tmp->mathgrade);
		tmp = tmp->next;
	}
	closefile(fp);
}
