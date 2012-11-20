#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define N 20

void swap(char *p, int i, int j)
{
	int tmp;
	tmp = p[i];
	p[i] = p[j];
	p[j] = tmp;
}

void reverse(char *p)
{
	int i = 0, j = strlen(p)-1;
	if(i >= j)
	  return ;
	swap(p, i, j);
	while(++i < --j)
	  swap(p, i, j);
}

void ftoa(double n, char *dest)
{
	char s[4];
	char t[10];	
	int sign = (int)(n);
	int flag = (int)(sign/100);
	int i = 0;
	do
	{
		s[i++] = sign%10 + '0';	
	}while((sign /= 10) > 0 && i < 2);
	s[i++] = '.';
	s[i] = '\0';
	reverse(s);
//	printf("%s\n", s);
	i = 0;
	int k = 1;
	do
	{
		t[i] = flag%10 + '0';
		if((k+i) % 3 == 0)
		{
			t[++i] = ',';
			k -= 1;
		}
		i++;
	}while((flag /= 10) > 0);
	t[i++] = '$';
	t[i] = '\0';
	reverse(t);
//	printf("%s\n", t);

	strcpy(dest, t);
	strcpy(dest+strlen(t), s);
	printf("%.2lf\t %s\n", n/100.0, dest);
}


void dollars(char *dest, char  *src)
{
	double val, power = 100.0;
	int i = 0;
	int len = strlen(src);
	for(val = 0.0; isdigit(src[i]); i++)
	  val = val*10.0 + (src[i] - '0');
	//printf("%s\t$%.2lf\n",src, val/power);
	ftoa(val, dest);

}

int main(int argc, char *argv[])
{
	char str[100];
	char dollar[100];
	strcpy(str, argv[1]);
	dollars(dollar, str);
	return 0;
}
