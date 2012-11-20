#include <stdio.h>
#include <string.h>
int main()
{
	char str[]="chyab";
	int i, l = strlen(str), j, k;
	for(i=l; i>0; i--){
		str[i] = str[i-1];
	}
	for(i=1; i<l; i++){
		if(str[0] < str[i])
			str[0] = str[i];
		
	}
	for(i=1; i<l; i++){
		if(str[i] == str[0])
			for(;i<=l;i++)
				str[i] = str[i+1];


	}
	for(k=0; k<l; k++)
		printf("%c\n",str[k]);


	return 0;
}

