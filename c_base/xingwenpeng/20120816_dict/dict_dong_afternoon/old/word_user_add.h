/*************************************************************************
    > File Name: word_default.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月14日 星期二 19时19分31秒
 ************************************************************************/
#ifndef WORD_DEFAULT_H_
#define WORD_DEFAULT_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <error.h>

#include "debug.h"
#define FILENAME "dict.txt"
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

void * wd_word_default(char *filename);

dict_elem_t * wd_read_elem_from_txt(char *filename, dict_elem_t *head_p, int w_count);

int wd_get_elem_count(char *filename);

void wd_print_data(dict_elem_t *head_p, int w_count);
#endif 
