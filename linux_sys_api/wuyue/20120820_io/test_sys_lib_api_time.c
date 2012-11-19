/*************************************************************************
    > File Name: test_sys_lib_api_time.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月20日 星期一 16时18分16秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>

int main(void)
{
#ifdef LIB_API_IO
	FILE *fp;
	char ch;
	int i;

	fp = fopen("test.bin", "r");
	for (i = 0; i < 1024 * 1024; i++)
		ch = fgetc(fp);
	fclose(fp);
#else
	int fd, i;
	char ch;

	fd = open("test.bin", O_RDONLY);
	for (i = 0; i < 1024 *1024; i++)
		read(fd, &ch, 1);
	close(fd);
#endif
	return 0;
}
