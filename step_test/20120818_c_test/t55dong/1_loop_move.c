/*************************************************************************
    > File Name: loop_move.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月18日 星期六 14时25分19秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#define SWAP(a, b) do {\
			char tmp;\
			tmp = a;\
			a = b;\
			b = tmp;\
		}while(0)
void loop_one(char *str)
{
	int len = strlen(str);

	while(--len > 0)
		SWAP(str[len], str[len-1]);
}

void loop_move(char *str, int n)
{
	while(n-- > 0)
		loop_one(str);
}
int main(void)
{
	char s[] = "abcdefghi";
	loop_move(s, 2);
	puts(s);

	return 0;
}
