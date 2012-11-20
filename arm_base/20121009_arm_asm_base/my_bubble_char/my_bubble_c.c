#include <stdio.h>
#include <string.h>

extern void bubble_sort(char *s, int len);

int main(void)
{
	char *s = "zxfcbahijknml";
	
	printf("Before sort: %s\n", s);
	bubble_sort(s, strlen(s));
	printf("After sort: %s\n", s);

	return 0;
}