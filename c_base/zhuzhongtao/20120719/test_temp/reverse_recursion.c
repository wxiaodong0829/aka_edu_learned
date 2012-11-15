/*************************************************************************
    > File Name: reverse_recursion.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月19日 星期四 15时16分22秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

char s[] = "abcdefg";
#define swap(type, x, y) {\
	type tmp;\
	tmp = x;\
	x = y;\
	y = tmp;\
}

void reverse(int l,int r)
{
	int ll = 0, rr = 0;
	if (l >= r) return ;
	else {
		swap(char, s[l], s[r]);
		//ll = l + 1;
		//rr = r - 1;
		//reverse(ll, rr);
		reverse(++l, --r);
	}
}
int main(void)
{

	printf("%s\n", s);
	reverse(0, strlen(s)-1);
	printf("%s\n", s);
}
