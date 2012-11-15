/*************************************************************************
    > File Name: strtok.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月25日 星期三 14时07分46秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
char *my_strtok(char *str, const char delim[])
{
	return str;
}
	
int main(void)
{
	int i;
	char s1[] = "Today is a wonderful day!";
	char str[5][10];
	char *str1 = NULL;
	char *token;
	
	for (i = 0, str1 = s1; ; i++, str1 = NULL) {
		if ((token = strtok(str1, " ")) == NULL)
			break;
		strcpy(str[i], token);
		printf("%s\n", str[i]);
	}
	return 0;
}
