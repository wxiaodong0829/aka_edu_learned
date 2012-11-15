#include <stdio.h>

int main(int argc, char *argv[])
{
		int a = (int)argv[1];
		int b = (int)argv[2];

		if(a > b)
				printf("a > b\n");
		else if(a == b)
				printf("a == b\n");
		else
				printf("a < b\n");

		return 0;
}
