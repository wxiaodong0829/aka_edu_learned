/*************************************************************************
    > File Name: time.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月23日 星期四 12时42分07秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t last;
	time_t now;
	int i = 0;

	struct tm t;
	struct tm *pt = &t;


	for (i = 0, last = time(NULL); i < 10; ) {
		if ((now = time(NULL)) > last) {
			last = now;
			i++;

			pt = localtime(&now);
			printf("%d:%d:%d\n", pt->tm_hour, pt->tm_min, pt->tm_sec);
		}
	}
	return 0;
}
