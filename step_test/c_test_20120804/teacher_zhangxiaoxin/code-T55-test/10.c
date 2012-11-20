#include <stdio.h>
#include <string.h>
#define N 4

typedef int (*fp_t) (int, int);
typedef struct 
{
	char op;
	fp_t fp;
}cmd_t;

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

int mul(int a, int b)
{
	return a * b;
}

int div(int a, int b)
{
	return a / b;
}

int main(void)
{
	cmd_t arr[N]  = {{'+', add}, {'-', sub}, {'*', mul}, {'/', div}};
	char c;
	int i, a, b; 

	while(1)
	{
		scanf("%c", &c);
		if(c == '#')
		{
			printf("quit!\n");
			break;
		}
		scanf("%d %d", &a, &b);
		getchar();
		for(i = 0; i < N; i++)
		{
			if(c == arr[i].op)
				printf("Result:%d\n", arr[i].fp(a, b));
		}
	}

	return 0;
}


