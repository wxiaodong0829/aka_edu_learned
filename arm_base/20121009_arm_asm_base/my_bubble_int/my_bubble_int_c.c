#include <stdio.h>
#include <string.h>

extern void bubble_sort(int *s, int len);

int main(void)
{
#if 0
	char *s = "zxfcbahijknml";
#endif
	int i, j;
	int s[20] = {9, 7, 8, 10, 11, 20, 0, 5, 12};	
	
	for (i = 0; i < 9; i++)
		printf("%4d", s[i]);
	printf("\n");
	bubble_sort(s, 9);
	for (i = 0; i < 9; i++)
		printf("%4d", s[i]);
	printf("\n");

	return 0;
}