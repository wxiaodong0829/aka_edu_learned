/*************************************************************************
    > file Name: wc.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年07月15日 星期日 17时36分14秒
 ************************************************************************/

#include<stdio.h>

#define IN  1 /* inside a world */
#define OUT 0 /* outside a world */

/* count lines, words, and characters in input */
int main(void)
{
	int c, nl, nw, nc, state;

	state = OUT;
	nl = nw = nc = 0;
	while((c = getchar()) != EOF) {
		++nc;
		if (c == '\n')
			++nl;
		//if (c == ' ' || c == '\n' || c == '\t')
		if (c == ' ' || '\n' == c || '\t' == c)
			state = OUT;
		else if (state == OUT) {
			state = IN;
			++nw;
		}
	}
	printf("nl=%d nw=%d nc=%d\n", nl, nw, nc);

	return 0;
}
