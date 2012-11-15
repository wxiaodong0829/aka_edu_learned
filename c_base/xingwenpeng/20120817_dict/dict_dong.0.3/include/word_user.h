/*************************************************************************
    > File Name: word_user.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月17日 星期五 08时48分20秒
 ************************************************************************/
#ifndef WORD_USER_H_
#define WORD_USER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "word_default.h"
#include "dict.h"

char *word_user(char *filename_user);
//当添加一个词条后，必须重新开始，才能再次加入查找范围

#endif
