#include<stdio.h>
#include<string.h>
int main(void)
{
	char str[]="achyab";
	char tmp;
	char max='\0';
	int i=0;
	int j;
	int m=strlen(str);
	for(i=0;i<m;i++)
	{
		if(str[i]>max)
		max=str[i];
	}
	for(i=m-1;i>0;i--)
	{
		if(str[i]==max)
		{
			tmp=str[i];
			for(j=i;i<m;i++)
			str[i]=str[i+1];
			str[0]=tmp;
		}
	}
	printf("%s\n",str);
//	printf("%c\n",max);
	return 0;
}
