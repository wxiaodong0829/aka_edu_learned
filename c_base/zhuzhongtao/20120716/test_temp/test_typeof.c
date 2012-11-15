/*************************************************************************
    > File Name: test_typeof.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月16日 星期一 14时52分09秒
 ************************************************************************/

#include<stdio.h>
typedef struct 
{
	int x;
	char y;
}astruct, * pastrcut;
int main()
{
	int sizem, sizew;
	int x = 3;
	typeof(&x) m;
	sizem = sizeof(m);
	*m = 5;
	typeof(((astruct *)5)->y) w;
	sizew = sizeof(w);
	w = 'a';
	return 1;
}
