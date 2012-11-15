/*************************************************************************
    > File Name: bst_book.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月22日 星期日 14时40分13秒
 ************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

typedef struct tnode *link;
struct tnode {				/*	树的节点		*/
	char *word;				/*	指向单词的指针	*/
	int count;				/*	单词出现的次数	*/
	link left;		/*	左子节点		*/	
	link right;	/*	右子节点		*/
};	
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

link NODE(link t, char *w, int count)
{
	t = malloc(sizeof *t);

	t->word = strdup(w);
	t->count = count;
	t->left = t->right = NULL;

	return t;
}

/*	单词出现频率的统计	*/
int main(void)
{
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

char *Strdup(char *);

link addtree(link p, char *w)
{
	int cond;
	if (p == NULL)  p = NODE(p, w, 1);
	else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else 
		p->right = addtree(p->right, w);
	return p;
}
void treeprint(link  p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

#include <stdlib.h>

char *Strdup(char *s)
{
	char *p;

	p =  malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void )
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}
