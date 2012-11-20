#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	int i;

	char max;

	char str[]={"chyab"};

	max = str[0];

	for(i=1;str[i];i++)
	{
		int tmp;
		if((max-str[i])<0)
		{
//			tmp=max;
//			max=str[i];
//			str[i]=tmp;
	
			max=str[i];
		}
			
		else 
			;

			return i;
	}
		printf("%c %d\n",max ,i);
	for(i=0;str[i];i++)
	printf("%c\n",str[i]);
	return 0;
}
