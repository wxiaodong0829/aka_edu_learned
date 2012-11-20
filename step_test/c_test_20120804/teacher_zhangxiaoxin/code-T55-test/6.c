#include <stdio.h>
#define N 1024

char * myitoa(int n, char *p, int radix)
{
	char index[] = "0123456789ABCDEFGHIGKLMNOPQRSTUVWXYZ";
	int i,j,k;
	int tmp;

	i = 0;
	if(radix == 10 && n < 0)
	{
		tmp = (unsigned)-n;
		p[i++] = '-';
	}
	else
		tmp = (unsigned)n;
	do
	{
		p[i++] = index[tmp % (unsigned)radix];
		tmp /= radix;
	}while(tmp);

	p[i--] = '\0';

	if(p[0] == '-')
		k = 1;
	else
		k = 0;

	char tmpch;
	for(j = k; j <= i; j++, i--){
		tmpch = p[j];
		p[j] = p[i];
		p[i] = tmpch;
	}
	/*
	for(j = k; j <= (i - k) / 2.0; j++)
	{
		tmpch = p[j];
		p[j] = p[i - j];
		p[i - j] = tmpch;
	}
	*/
	printf("p = %s\n", p);
	return p;

}

int main(int argc, char *argv[])
{
	int n;
	char str[N];

	printf("please input a num:");
	scanf("%d", &n);

	myitoa(n, str, 10);
	printf("n = %d   str = %s\n", n, str);
	return 0;
}
