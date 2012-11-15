/*************************************************************************
    > File Name: word_default.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月17日 星期五 08时34分05秒
 ************************************************************************/

/******************************************wd.h***/
#ifndef WORD_DEFAULT_H_
#define WORD_DEFAULT_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <error.h>

#include "debug.h"
#include "dict.h"

dict_elem_t *read_to_mem_from_txt(char *filename, dict_elem_t *head_p, int w_count);


#endif 

