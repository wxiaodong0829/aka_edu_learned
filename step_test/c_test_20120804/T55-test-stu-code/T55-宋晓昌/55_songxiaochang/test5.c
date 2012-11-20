#include<stdio.h>
#include<string.h>
#include<ctype.h>
void fun(char str[],int n)
{
	int i,j,end;
	char tmp;
	for(i=end=n-1;i>=0;i--)
	{
		if(isdigit(str[i]))	
		{
			tmp=str[i];
			for(j=i;i<end;i++)
				str[i]=str[i+1];
				str[end--]=tmp;
		}
			
	
	}
}
int main(void)
{
	char str[]="song123xiao343chan56";
    int m=strlen(str);
	 fun(str,m);
	 printf("%s\n",str);
	return 0;
}

