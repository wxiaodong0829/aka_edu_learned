/*************************************************************************
    > File Name: err.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月21日 星期二 16时15分28秒
 ************************************************************************/
#include "err.h"
void error_sys(const char *err)
{
	 perror(err);
	 exit(1);
}
void error_user(const char *err)
{
	puts(err);
	exit(2);
}


