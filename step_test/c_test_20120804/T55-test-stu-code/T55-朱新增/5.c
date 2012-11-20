#include <stdio.h>
#include <string.h>
#include <ctype.h>
char *fun(char src[100])
{
	char tmp;

	int i, j,end;

	for(i = end = strlen(src) - 1; i >= 0; i--){

		if(isdigit(src[i])){

			tmp = src[i];

			for(j = i; i < end; i++)

				src[i] = src[i + 1];

	                   	src[end--] = tmp;
		}
	}
	return src;
}
int main(void)
{
	char src[100];

	printf("Input src:");

	scanf("%s", src);

	fun(src);

	printf("src:%s\n", src);

	return 0;
}
