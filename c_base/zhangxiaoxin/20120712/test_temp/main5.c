#include <stdio.h>

int main(void)
{
		int a = 0,b = 3,c = 10;
//		if((a && b) && ++c)
//				printf("b = %d\n",b);
		printf("sizeof(++c) = %d\nc = %d\n", sizeof(++c),c);
		printf("c = %d\n", c);

		return 0;
}
