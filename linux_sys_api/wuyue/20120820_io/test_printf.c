/*************************************************************************
    > File Name: test_printf.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月20日 星期一 21时24分01秒
 ************************************************************************/

int printf(const char *format, ...);
#ifdef DEBUG
int i = 1;
#endif
int main(void)
{
#ifndef DEBUG
	int i = 1;
#endif
	printf("%d %d %d\n", i, i++, ++i);
	return 0;
}
