#include <stdio.h>

#define N 1024

int main(int argc, const char *argv[])
{
		char str[N];

		printf("Please enter <hello world>:");
		gets(str);
		printf("%s\n",str);

		switch(0){
				case 10: printf("10 10 10");
				case 11: printf("11 11 11");
		}

		return 0;
}
