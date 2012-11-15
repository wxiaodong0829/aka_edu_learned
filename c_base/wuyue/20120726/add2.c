/*************************************************************************
    > File Name: add.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月26日 星期四 15时45分33秒
 ************************************************************************/
int add(int a, int b)
{
	int r[5];
	r[0] = a + b;
	return r[0];
}
int main(void)
{
	int c;

	c = add(100, 200);

	return 0;
}
