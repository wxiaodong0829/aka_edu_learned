#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char str[] = "cnaoeobanbzhyab";
	char tmp = str[0];
    int i, k=0;

	printf("%s\n", str);
	
	for(i=1; i<=strlen(str);i++)
		if(tmp < str[i])
		{
			k = i;
			tmp = str[i];
		}

	for(i=k; i>0; i--)
		str[i] = str[i-1];

	str[0] = tmp;

	printf("%s\n", str);

	return 0;
}
