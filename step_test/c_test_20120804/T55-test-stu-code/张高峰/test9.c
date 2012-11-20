#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define N 100

#define typedef char * va_list;
#define _Bnd(X,bnd) (sizeof(X)+(bnd) & ~(bnd))
#define va_start(ap,A) (void)((ap)=(char *)&(A) + _Bnd(A,3U))
#define va_arg(ap,T) (*(T *)(((ap) +=_Bnd(T,3U))-_Bnd(T,3U)))
#define va_end(ap) (void)0

char * vstrcat(const char *f,...)
{
	int m=strlen(f),i;
	va_list ap,p,g;
	p=malloc(N*sizeof(char));
	strcpy(p,f);
	va_start(ap,f);
	while((g=va_arg(ap,char *))!=NULL)
	{
		for(i=0;g[i];i++)	
			p[m++]=g[i];
	}
	p[m]='\0';
	va_end(ap);
	return p;
}

int main(void)
{
	char *p;
	p=vstrcat("hello world"," china "," where are you ",NULL);
	printf("%s\n",p);

	return 0;
}
