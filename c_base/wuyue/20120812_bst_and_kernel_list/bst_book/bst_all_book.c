/*************************************************************************
    > File Name: bst_all_book.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月13日 星期一 10时38分45秒
 ************************************************************************/

/***************
 *
 * bst.h
 *
 * ***********/
#ifndef BST_H
#define BST_H

typedef struct node *link;
struct node {
	unsigned char item;
	link l, r;
};

link search(link t, unsigned char key);
link insert(link t, unsigned char key);
link delete(link t, unsigned char key);
void print_tree(link t);

#endif 

/***************
 *
 * bst.c
 *
 * ***********/
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
static link make_node(unsigned char item)
{
	link p = malloc(sizeof *p);
	p->item = item;
	p->l = p->r = NULL;
	return p;
}

static void free_node(link p)
{
	free(p);
}

link search(link t, unsigned char key)
{
	if (!t)
		return NULL;
	if (key < t->item)
		return search(t->l, key);
	if (t->item < key)
		return search(t->r, key);

	/* if (t->item == key) */
	return t;
}

link insert(link t, unsigned char key)
{
	if (!t)
		return make_node(key);
	if (key < t->item)				/* insert to left subtree */
		t->l = insert(t->l, key);
	else							/* if (t->item <= key),  insert to right subtree */
		t->r = insert(t->r, key);
	return t;
}
link delete(link t, unsigned char key)
{
	link p;
	if (!t)
		return NULL;
	if (key < t->item)				/* delete from left subtree */
		t->l = delete(t->l, key);
	else if (t->item < key)			/* delete from right subtree */
		t->r = delete(t->r, key);
	else {							/* if (t->item == key)		*/
		if (t->l == NULL && t->r == NULL) { /* if t is leaf(叶子) node*/
			free_node(t);
			t = NULL;				/*待返回*/
		} else if (t->l) { /* if t has left subtree (巧妙之处：将删除根节点转移为删叶子节点，使更快,效率更高)*/
			/* replace t with the rightmost node in left subtree */
			for (p = t->l; p->r; p = p->r) /* find the rightmost node in left subtree(找左子树中最右边即左子树中最大的节点)*/
				;							/* 找根节点的继任者 */
			t->item = p->item;				/* 为继任者加冕，占据根的位置 */
			t-l = delete(t->l, t->item);	/* 递归删除继任者原来在的叶子节点*/
		} else {
			for (p = t->r; p->l; p = p->l)
				;
			t->item = p->item;
			t->r = delete(t->r, t->item);
		}
	}
	
	return t;
}

void print_tree(link t)
{
	if (t) {
		printf("(");
		printf("%d",t->item);
		print_tree(t->l);
		print_tree(t->r);
		printf(")");
	} else
		printf("()");
}

/*******************************
 *
 *		main.c
 *
 ******************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

#define RANGE 100
#define N 6

void print_item(link p)
{
	printf("%d", p->item);
}
int main()
{
	int i, key;
	link root = NULL;
	srand(time(NULL));
	for (i = 0; i < N; i++)
		root = insert(root, rand() % RANGE);
	printf("\t\\tree");
	print_tree(root);
	printf("\n\n");
	while (root) {
		key = rand() % RANGE;
		if (search(root, key)) {
			printf("delete %d in tree\n", key);
			root = delete(root, key);
			printf("\t\\tree");
			print_tree(root);
			printf("\n\n");
		}
	}
}
