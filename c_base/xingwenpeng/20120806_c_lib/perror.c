/*************************************************************************
    > File Name: perror.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月06日 星期一 16时37分08秒
 ************************************************************************/

#include <stdio.h>

int main(void)
{
	FILE *fp;
	if ((fp = fopen("asdf;alksfg", "r")) == NULL) {
		perror("fopen asdf;alksfg");
		exit(-1);
	}
	return 0;
}
