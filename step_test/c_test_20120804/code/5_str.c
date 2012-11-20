/*************************************************************************
    > File Name: 5_str.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月04日 星期六 13时14分44秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define swap(x, y) do{char tmp; tmp = x; x = y; y = tmp;}while(0)

void str_str(char * str)
{
	int i, j;
	int len = strlen(str);
	int r = len - 1;

	for (i = r; i > 0; i--) {
		if (str[i] >= '0' && str[i] <= '9') {
			j = i;
			while (j < r) {
				swap(str[j], str[j+1]);
				j++;
			}
			r--;
		}
	}

}
int main(void)
{
	char str[] = "asd123fgh543df";
	printf("%s\n", str);
	str_str(str);
	printf("%s\n", str);
	return 0;
}
