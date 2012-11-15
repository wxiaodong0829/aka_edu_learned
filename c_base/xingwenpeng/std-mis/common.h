#ifndef __COMMON_H__
#define __COMMON_H__
#include <stdio.h>
typedef struct node *link_t;
typedef struct node{
	unsigned ID;
	char name[20];
	float chgrade;
	float mathgrade;
	float average;
	link_t next;
}node_t;

FILE *openfile(char *name, int flag);
void closefile(FILE *);
link_t creat(char *name, int flagbyaverage, link_t head);
void link_destroy(link_t head);
link_t deleterecord(char *filename, link_t head);
link_t insertrecord(char *filename, link_t head);
link_t sortbyaverage(char *filename, int flagbyaverage, link_t head);

#endif
