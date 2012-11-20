#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define M 10 
#define N 15

void fun(char *s)
{
	int i, j = 0, k = 0;
	char buf_num[M];
	char buf_str[N];
		for(i = 0; s[i] != '\0'; i++)
		{
			if(isdigit(s[i]))
			{
				buf_num[k] = s[i];
				k++;
			}
			if(isalpha(s[i]))
			{
				buf_str[j] = s[i];
				j++;
			}
		}
	strcat(buf_str, buf_num);
	printf("%s\n", buf_str);

}
int main()
{
	int i;
	char s[] = "a2111aaa222";
	fun(s);

	return 0;

}
