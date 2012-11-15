/*************************************************************************
    > File Name: binary_default.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月14日 星期二 19时42分12秒
 ************************************************************************/
#ifndef BINARY_DEFAULT_H_
#define BINARY_DEFAULT_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "debug.h"

/********************
 *
 *  search from binary famot
 *
 * ****************/
typedef struct dict_bin {
	int key_len;
	char *key;
	int n_trans;
	char **trans;
}dict_bin_t;

void * bd_binary_default(char *txt_file_name, char *index_file_name);

#endif
