#include <stdio.h>

int main(void)
{
		int a = 0,b = 3,c = 4;
		if((a && b) && ++c)
				printf("b = %d\n",b);
		printf("c = %d\n", c);

		return 0;
}
