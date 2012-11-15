/*************************************************************************
    > File Name: binary_default.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月17日 星期五 08时47分33秒
 ************************************************************************/
#ifndef __BINARY_DEFAULT_H_
#define __BINARY_DEFAULT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "word_default.h"
#include "dict.h"


dict_elem_t *bd_fread(FILE *fbp, dict_elem_t *b_head_p, int w_count);
void *bd_fwrite(dict_elem_t *b_head_p, int w_count, char *binary_file_name);
char *binary_default(void);

#endif
