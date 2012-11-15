/*************************************************************************
    > File Name: fopen.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月06日 星期一 10时06分11秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int res;

	if (argc < 2) {
		printf("fopen need a filename\n");
		exit(-1);
	}
	if ((fp = fopen(argv[1], "a+")) == NULL) {
		printf("error open abcd \n");
		exit(-1);
	}

	res = fclose(fp);
	printf("%d\n", res);
	return 0;
}
