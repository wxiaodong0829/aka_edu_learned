#include <stdio.h>
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
int dev(int a, int b)
{
	if (b==0) {
		printf("除数不能为0\n");
		return -1;
	} else
		return (int)(a / b);
}
int calculator(int a, int b, int (*cal)(int a, int b))
{
	return cal(a, b);
}
int main()
{
	int ret;
	int a, b;
	char c;
	scanf("%c\n%d %d", &c, &a, &b);
	switch (c) {
		case '+':
			ret = calculator(a, b, add);
			break;
		case '-':
			ret = calculator(a, b, sub);
			break;
		case '*':
			ret = calculator(a, b, mul);
			break;
		case '/':
			ret = calculator(a, b, dev);
			break;
			
	}
	if (ret == -1)
		return 0;
	printf("%d\n", ret);
	return 0;
}

