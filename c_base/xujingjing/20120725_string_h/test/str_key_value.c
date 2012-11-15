/*************************************************************************
    > File Name: str_key_value.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月25日 星期三 16时12分44秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#define MAXBUF 200

int main(void)
{
	int i, j, k;
	char tmp[MAXBUF][MAXBUF];
	char key[MAXBUF];
	char value[MAXBUF];
	char str[] = "http://www.google.cn/search?complete=1&hl=zh-CN&ie=GB2312&q=linux&meta=";
	char *strtmp = NULL;
	char *token = NULL;

	for (i = 0, strtmp = str; (token = strtok(strtmp, "?&")); strtmp = NULL) {
		strcpy(tmp[i++], token);
		printf("%s\n", token);
	}
	for (j = 0; j < i; j++)	
		for(k = 0, strtmp = tmp[j]; 1;strtmp = NULL, k++) {
			if ((token = strtok(strtmp, "=")) == NULL) {
				printf("\n");
				break;
			}
			if (k % 2 == 0) {
				strcpy(key, token);
				printf("key = %s\t", key);	
			} else {
				strcpy(value, token);
				printf("valuer = %s", value);
			}
		}

	return 2;
}
