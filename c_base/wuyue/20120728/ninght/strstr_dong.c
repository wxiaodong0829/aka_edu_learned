/*************************************************************************
    > File Name: strstr_dong.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月28日 星期六 16时32分42秒
 ************************************************************************/

#include <stdio.h>

int main(int argc, char *argv[])
{
	char *str;
	str = argv[1];
//	char str[] = "abceee*aaadff";
	if (argc < 2) {
		printf("please input more argv")
	}
		
	int len = 1;
	int i, j;
	int l = 0, r = 0;
	int maxl = 0, maxr = 0;

	for (i = 0, len = 1; str[i]; i += r - l + 1) {
		for (l = r = i; str[r] == str[r+1]; r++)
			;
		if (len <= r - l + 1) {
			len = r - l + 1; maxl = l; maxr = r;
		}
	}

	printf("maxlen = %d str[] = ", len);
	for(i = maxl; i <= maxr; i++) {
		printf("%c", str[i]);
	}
	printf("\n");
	return 0;
}
