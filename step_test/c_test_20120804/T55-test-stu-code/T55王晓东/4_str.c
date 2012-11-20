/*************************************************************************
    > File Name: 4_str.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月04日 星期六 12时53分25秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#define swap(x, y) do{char tmp; tmp = x; x = y; y = tmp;}while(0)
void str_str(char *str)
{
	int index = 0;
	int i;
	int len = strlen(str);

	for (i = 1; i < len; i++) {
		if (str[index] < str[i])
			index = i;
	}
	i = index;
	while (i-- > 0) {
		swap(str[index], str[i]);
		index--;
	}
}
int main(void)
{
	char str[] = "abdcdzdg";
	printf("%s\n", str);
	str_str(str);
	printf("%s\n", str);


	return 0;
}
