/*************************************************************************
    > File Name: creat_test_bin.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月20日 星期一 16时22分17秒
 ************************************************************************/

#include <stdio.h>

int main(void)
{
	FILE *fp;
	int i;
	char buf[1024];

	fp = fopen("test.bin", "w");

	for (i = 0; i < 1024; i++)
		fwrite(buf, sizeof(buf), 1, fp);
	fclose(fp);

	return 0;
}
