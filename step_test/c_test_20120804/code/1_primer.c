/*************************************************************************
    > File Name: primer.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月04日 星期六 09时45分58秒
 ************************************************************************/

#include <stdio.h>
#include <math.h>

int main(int argc, char * argv[])
{
	int i, j, k, n;
	int flag = 1;
	scanf("%d", &n);

	if (n <= 2) {
		for (i = 0; i < n; i++)
			printf("%4d", i+1);
		printf("\n");
		return 0;
	}

	printf("%4d%4d", 1, 2);
	for (i = 3, k = 0; i <= n; i += 2) {
		flag = 1;
		for (j = 2; j*j <= i; j++)
			if (i%j == 0) {flag = 0; continue;}
		if (flag == 1) {
			k++;
			printf("%4d%s", i, k%10 == 0 ? "\n" : "");
		}
	}
	printf("\n");
	return 0;
}
