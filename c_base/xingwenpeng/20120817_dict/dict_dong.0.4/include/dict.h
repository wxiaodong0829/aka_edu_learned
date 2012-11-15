/*************************************************************************
    > File Name: dict.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月17日 星期五 08时35分26秒
 ************************************************************************/

#ifndef DICT_H_
#define DICT_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <error.h>

#include "debug.h"


typedef struct dict_elem {
	char *key;
	int n_trans;
	char **trans;
} dict_elem_t;


void print_one_elem(dict_elem_t *word_p);
void print_data(dict_elem_t *head_p, int w_count);
int get_elem_count(char *filename);
void shell_sort(dict_elem_t *head_p, int l, int r);
dict_elem_t *search(dict_elem_t *head_p, int w_count);
void distory(dict_elem_t *head_p, int w_count);




#endif 
