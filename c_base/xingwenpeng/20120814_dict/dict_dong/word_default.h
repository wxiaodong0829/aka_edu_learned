/*************************************************************************
    > File Name: word_default.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月14日 星期二 19时19分31秒
 ************************************************************************/
#ifndef WORD_DEFAULT_H_
#define WORD_DEFAULT_H_

#define <stdio.h>
#define <stdlib.h>
#define <ctype.h>
#define <string.h>

#define "debug.h"
/********************
 *
 *  search from txt famot
 *
 * ****************/
typedef struct dict_elem {
	char *key;
	int n_trans;
	char **trans;
} dict_elem_t;

dict_elem_t * wd_word_default(char *filename);

static int wd_get_elem_count(char *filename);

static dict_elem_t * wd_read_elem_from_txt(FILE *fp, dict_elem_t *head_p, int w_count);

static dict_elem_t * wd_read_key(FILE *fp, dict_elem_t *word_p);

static dict_elem_t * wd_read_trans(FILE *fp, dict_elem_t *word_p);


static void wd_shell_sort(dict_elem_t *head_p, int l, int r);

static void wd_binsearch(dict_elem_t *head_p, char *key_word);


#endif 
