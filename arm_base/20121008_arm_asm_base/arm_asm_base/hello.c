#include <stdio.h>

int main(void)
{
	volatile int i; 
	for (i = 0; i < 10; i++) {
		printf("i is %d\n", i);
	}
	
	return 0;
}