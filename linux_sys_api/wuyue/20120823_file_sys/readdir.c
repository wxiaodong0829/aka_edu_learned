/*************************************************************************
    > File Name: readdir.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月23日 星期四 14时39分12秒
 ************************************************************************/

#include <stdio.h>
#include <dirent.h>
#include "err.h"

int main(void)
{
	struct dirent *p;
	DIR *dirp;

	if ((dirp = opendir(".")) == NULL)
		error_sys("opendir");

	while (1) {
		if ((p = readdir(dirp)) == NULL)   // 文件结尾: NULL	非结尾：文件结构指针
			break;
		if (p->d_name[0] != '.')
			puts(p->d_name);
	}

	return 0;
}
