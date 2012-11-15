/*************************************************************************
    > File Name: main.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月16日 星期四 16时32分42秒
 ************************************************************************/
#include "dict.h"
#include "word_default.h"
#include "word_user.h"
#include "debug.h"

#define FILE_DEF "/opt/dict_dong/dict.txt"
#define FILE_USER "~/soft_dong/dict_dong/dict_new.txt"

int main(int argc, char *argv[])
{
	char *ret;
	ret = word_user(FILE_DEF, FILE_USER);
	if (ret == (char *) 1) {
		puts("Think you enjoy it!");
	} else if (ret == (char *) 2) {
		puts("error!!!");
		exit(-1);
	}

	return 0;
}
