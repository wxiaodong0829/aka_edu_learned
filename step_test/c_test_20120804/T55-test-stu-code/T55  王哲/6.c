#include <stdio.h>
#include <string.h>
char *myitoa(int n, char *p)
{

	int i=0,sign;
	sign = n;
	if(n<0) n = -n;
	do{
		p[i++] = n%10 + '0';
	}while(n = n/10);

	if(sign < 0) p[i++] = '-';
	*(p + i) = '\0';

	return p;
}
void re(char *p)
{
	int i, l;
	l = strlen(p) - 1;
	char temp;
	for(i=0,l; i<l; i++, l--){
		temp = p[i];
		p[i] = p[l];
		p[l] = temp;
	}
}

int main()
{
	char s[100];
	int n;
	printf("write number:");
	scanf("%d", &n);

	myitoa(n, s);
	re(s);
	printf("%s\n", s);
	return 0;
}
