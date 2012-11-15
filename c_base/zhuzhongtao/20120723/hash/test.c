/*************************************************************************
    > File Name: test.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年10月10日 星期三 08时46分20秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 101

typedef struct node *link;
struct node {
	char *name;
	char defn;
	link next;
};
static link hashtab[HASHSIZE]; /*指针表*/
link NODE(char *name, char *defn, link next)
{
	link t = malloc(sizeof *t);
	if (t == NULL) {
		printf("error malloc");
		return 0;
	}
	t->name = strdup(name);
	t->defn = strdup(defn);
	if (t->name == NULL || t->defn == NULL) {
		printf("error malloc");
		return 0;
	}
	t->next = next;

	return t;
}
void init()
{
	int i;
	for (i = 0; i < HASHSIZE; i++)
		hashtab[i] = NULL;
}
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}
link lookup(char *s)
{
	link np;

	for (np = hashtab[hash(s)]; np; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}
link install(char *name, char defn)
{
	link np;
	unsigned hashval;

	if ((np = lookup(name)) != NULL) {/* fund */
		free(np->defn);
		np->defn = defn;
	} else { /* not fund */
		np = NODE(name, defn, NULL);
		np->next = hashtab[hash(name)];
		hashtab[hash(name)] = np;
	}
	return np;
}
