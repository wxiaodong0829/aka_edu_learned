#include <stdio.h>
#include <string.h>
#define M 512
char buf[M];
void find_mstr(char buf[])
{
	int i, j, len = strlen(buf)-1, flag=0;
	char c=buf[0];
	for (i=1; i<len; i++) {
		if (buf[i]>c) {
			c = buf[i];
			flag = i;
		}
	}
	for (j=flag-1; j>=0; j--) {
		buf[j+1] = buf[j];
	}	
	buf[0] = c;
}
int main()
{
	scanf("%s", buf);	
	printf("%s\n", buf);
	find_mstr(buf);
	printf("%s\n", buf);
	return 0;
}
