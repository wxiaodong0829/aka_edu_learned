/*
 * =====================================================================================
 *
 *       Filename:  4.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年08月04日 15时19分32秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <stdio.h>

void strmax(char *p)
{
	int i, k, j;
	char tmp = p[0];
	for (i=0; p[i]; i++)
		if(tmp < p[i])
		{
			tmp = p[i];
			k = i;
		}
	for (j=k; j>=0; j--)
		p[j] = p[j-1];
	p[0] = tmp;
}
int main()
{
	char str[]="chyab";
	strmax(str);
	printf("%s\n", str);
	return 0;
}
