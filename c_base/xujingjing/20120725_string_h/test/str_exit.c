/*************************************************************************
    > File Name: str_exit.c
    > Author: wxxaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月25日 星期三 15时00分16秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#define MAXBUF 100
int main(void)
{
	int x = 0, y = 0;
	char in[MAXBUF];
	char *str1 = NULL, *strtmp = NULL;
	char *str[] = {
		"hello world",
		"hello hell",
		"hello aka",
		"hello hello hoho asdflk asdflkj asdfl asfd asdfl;kj "
	};
//	printf("%d\n\n", sizeof(str)/sizeof(str[0]));

	do  {
		scanf("%s", in);
		for (x = 0; x < sizeof(str)/sizeof(str[0]); x++)
			for(str1 = str[x]; (strtmp = strstr(str1, in)); str1 = strtmp + strlen(in)) {
				y = strtmp - str[x];
				printf("found %s !x = %d, y = %d\n", in, x, y);
			}
	} while (strcmp(in, "exit") != 0);
	return 0;
}
