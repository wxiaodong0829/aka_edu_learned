/*************************************************************************
    > File Name: realloc.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月07日 星期二 10时03分47秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ADD 5 
#define MAXNUM 20

int main(void)
{
	int i;//
	int in;
	int *p = realloc(NULL, ADD*sizeof(int));
	int *tmp = p;
	int time_realloc = 0;
	int flag_quit = 0;
	int in_num = 0;
	char s[MAXNUM];

	while (1) {
		for (i = 0; i < ADD; i++) {
			if ((fgets(s, MAXNUM, stdin)) == NULL) {
				flag_quit = 1;
				break;
			}
			if (s[strlen(s)-1] == '\n')
				s[strlen(s)-1] = '\0';
			in = atoi(s);
			printf("%5d\n", in);
			if (in == -1) {
				flag_quit = 1;
				break;
			}
			in_num++;
			tmp[i] = in;
		} 
		if ( flag_quit == 1)
			break;
		time_realloc++;
		tmp = realloc(p, (1 + time_realloc)*ADD*sizeof(int));
		//free(p);
		p = tmp;
		tmp = p + (ADD * time_realloc);
	}
	for (i = 0; i < in_num; i++) {
		printf("%5d", p[i]);
	}
	printf("\n");
	free(p);
	return 0;

}
