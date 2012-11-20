#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
	char s[100], temp;
	
	int i, l;
	printf("write:");
	
	scanf("%s", s);

	l = strlen(s) - 1;
	for(i = l;i>=0;i--)
		if(isdigit(s[i])){
			temp = s[i];
			for(;i<l;i++)
			s[i] = s[i+1];
			s[l] = temp;
			l--;
		}

	printf("%s\n", s);
	
	
	return 0;
}
