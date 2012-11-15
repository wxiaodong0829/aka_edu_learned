/*************************************************************************
    > File Name: strstr.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月25日 星期三 14时35分05秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
char *my_strstr(const char *src, char *substr)
{
	char *strtmp = NULL;
	return strtmp;
}
int main(int argc, char *argv[])
{
	int count = 0;
	int i;
	char *strtmp = NULL;
	char *str = NULL;

	if (argc < 3) {
		printf("you should gave me more three word!");
		return -1;
	}
	for (i = 0, count = 0, str = argv[1]; (strtmp = strstr(str, argv[2])); str = strtmp + strlen(argv[2]), count++)
		printf("%s\n", strtmp);
	printf("count = %d\n", count);
	return 0;	
}
