/*************************************************************************
    > File Name: read_from_file.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月08日 星期三 16时05分37秒
 ************************************************************************/
#include "link.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
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
FILE *link_read_file(const char * filename, node_t **head)
{
	FILE *fp;
	if ((fp = fopen(filename, "r+")) == NULL) {
		perror("fopen in: ");
		return NULL;
	}
	if ((*head = read_from_in(fp, *head)) == NULL) {
		printf("read_from_in  error");
		return NULL;
	}
	return fp;
}

