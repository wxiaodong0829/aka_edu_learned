#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *str_move(char str[])
{
	int len=strlen(str)+1; 
	int i, c_count=0, num_count=0;
	char *c = malloc(sizeof(len));	
	char *num = malloc(sizeof(len));
	for (i=0; i<=len; i++) {
		if (str[i]>='a' && str[i]<='z') {
			*(c + c_count) = str[i];
			c_count++;
		} else {
			*(num + num_count) = str[i];
			num_count++;
		}
	}
	*(c + c_count) = '\0';
	*(num + num_count) = '\0';
	strcat(c, num);
	return c;
}
int main()
{
	char str[]="asd123fgh543df";
	printf("%s\n", str);
	str_move(str);
	printf("%s\n", str_move(str));
	return 0;
}
