#include <stdio.h>
#include <string.h>

int main ()
{
	char s[]="chyab";
	int max, i,j;
	char tmp;
	int l =0,r =strlen(s);

	max =l;
	for(i =l+1; i < r; i++)
	{
		if(s[max] <s[i])
			max =i;
		tmp =s[max];
	}
	for( j =max; j >=0; j--)
		s[j] =s[j -1];
	s[l] =tmp;
	printf("%s\n",s);

	return 0;
}
