/*************************************************************************
    > File Name: strstr_dong.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月28日 星期六 16时32分42秒
 ************************************************************************/

#include <stdio.h>
#define MAXLEN 100

int main(int argc, char *argv[])
{
//	char *str;
//	str = argv[1];
	char str[] = "abceee*aaadff";
//	if (argc < 2) {
//		printf("please input more argv")
//	}
		
	int len[MAXLEN];
	int i, j;
	int nstr;
	int l[MAXLEN];
	
	j = MAXLEN;
	while (j-- > 0) {
		len[j] = 0;
		l[j] = 0;
	}

	if (str[0] != '\0') nstr = 1;
	else {
		printf("your string is NULL");
		return -1;
	}

	for (i = 0, j = 0; str[i]; i++) {
		if (str[i] == str[i+1]) {
			len[j]++;
		} else {
			len[j]++;
			l[++j] = i + 1;
			if (str[i+1] != '\0')
				nstr++;
		}
	}

	return 0;
}
