#include<stdio.h>
#include<string.h>

#define N 100

void dollars(char *dest,char const *src)
{
	int m=strlen(src),i=0,j=0,l,g,t=0,flag=0;
	l=m;
	dest[i++]='$';
	
	if(m<=2)	
	{
		dest[i++]='0';
		dest[i++]='.';
		if(m<=1)
		{
			dest[i++]='0';
			dest[i++]=src[j];
		}
		if(m==2)
		{
			dest[i++]=src[j++];
			dest[i++]=src[j];
		}
		dest[i]='\0';
		return;
	}
	else if(m<=5)
	{
		while(l>2)
		{
			dest[i++]=src[j++];
			l--;
		}
		dest[i++]='.';
		dest[i++]=src[j++];
		dest[i++]=src[j++];
		dest[i]='\0';
	}
	else
	{
		l=l-2;
		g=l%3;
		if(g)
		{
			while(j<g)
				dest[i++]=src[j++];
			dest[i++]=',';
		}
		l=l-g;
		while(l>0)
		{
			if(t%3==0&&flag!=0)	
			{
				dest[i++]=',';
				if(l==0)
					break;
			}
			dest[i++]=src[j++];
			l--;
			t++;
			flag=1;
		}
		dest[i++]='.';
		dest[i++]=src[j++];
		dest[i++]=src[j++];
		dest[i]='\0';

	}
}


int main(void)
{
	char src[N],dest[N];
	scanf("%s",src);
	dollars(dest,src);
	printf("input      output\n");
	printf("%s              %s\n",src,dest);
	return 0;
}
