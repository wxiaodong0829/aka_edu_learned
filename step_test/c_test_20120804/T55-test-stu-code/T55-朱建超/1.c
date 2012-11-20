/*
 * =====================================================================================
 *
 *       Filename:  1.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月04日 10时45分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>

int main()
{
	int n, i, j;
	scanf("%d", &n);
	printf("2\n");
	for (i=3; i <= n; i+=2){
		for (j=2; j*j<i; j++)
			if(i%j==0)
				break;
		if(j*j>i)
			printf("%d\n", i);
	}

	return 0;
}
