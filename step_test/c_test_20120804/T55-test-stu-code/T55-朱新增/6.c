#include<stdio.h>
char *myitoa(int n,char *p)
{	

	char tmp;

	int i,j;

	int sign;

	if ((sign = n)<0)

		n = -n;
	i=0;

	do{
		p[i++]= n % 10+'0';

	}while(n/=10);

	if(sign < 0)

		p[i++] = '-';

	p[i]='\0';

	for(--i,j=0;j<=i;i--,j++){

		tmp = p[j];

		p[j] = p[i];

		p[i] = tmp;


	}
	return p;
}
int main()
{
	int n;

	char p[15];

	printf(" inout n:");

	scanf("%d",&n);

	printf("%s\n",myitoa(n,p));

	return 0;
}
