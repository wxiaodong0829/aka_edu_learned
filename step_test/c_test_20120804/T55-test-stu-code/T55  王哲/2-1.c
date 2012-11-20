#include <stdio.h>

int main()
{
	int num[10], i;
	for(i=0; i<10; i++)
		num[i] = rand()%100;
	int j, k, l, temp;
	for(j=0; j<9; j++){
		k = j;
	
	for(l=j+1; l<10; l++)
		if(num[k] > num[l])
			k = l;
		
	if(k != j){
		temp = num[j];
		num[j] = num[k];
		num[k] = temp;
	
	}
	}
	for(i=0;i<10;i++)
		printf("%d\n", num[i]);

	
}
