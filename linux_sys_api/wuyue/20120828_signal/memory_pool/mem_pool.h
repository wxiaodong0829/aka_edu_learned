/*************************************************************************
    > File Name: mem_pool.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月29日 星期三 08时40分36秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include  "debug.h"
#include <errno.h>
#include "err.h"
#include <string.h>

typedef struct mem_ctl {
	int left;	// 此４Ｋ还剩多少
	char *cur;	//　当前指向何处
	struct mem_ctl *next; //下一块４Ｋ的地址
}memctl_t;
#define SIZ_M 4096



void *mem_pool(size_t size);
int mem_pool_free(void);
