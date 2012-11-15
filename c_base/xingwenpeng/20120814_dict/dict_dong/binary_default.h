/*************************************************************************
    > File Name: binary_default.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月14日 星期二 19时42分12秒
 ************************************************************************/
#ifndef BINARY_DEFAULT_H_
#define BINARY_DEFAULT_H_

#define <stdio.h>
#define <stdlib.h>
#define <ctype.h>
#define <string.h>

#define "debug.h"
/********************
 *
 *  search from binary famot
 *
 * ****************/
typedef struct dict_bin {
	int key_len;
	char *key;
	int trans_num;
	char **trans;
}dict_bin_t;

dict_bin_t * bd_binary_default(char *txt_file_name, char *index_file_name);

static int bd_get_elem_count(char *filename);

static dict_bin_t * bd_read_elem_from_bin(FILE *fp, dict_bin_t *head_p, int w_count);

static dict_bin_t * bd_read_key(FILE *fp, dict_bin_t *word_p);

static dict_bin_t * bd_read_trans(FILE *fp, dict_bin_t *word_p);

static void bd_shell_sort(dict_elem_t *head_p, int l, int r);

static void bd_binsearch(dict_elem_t *head_p, char *key_word);



dict_index_t * bd_write_binary(dict_index_t *head_p);

