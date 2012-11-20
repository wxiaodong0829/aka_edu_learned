#include <stdio.h>

int main()
{
	int num[10];
	int i, j, k, n, f,temp;
	
	for(i=0; i<10; i++)
		num[i] = rand()%100;
	for(j=0; j<9; j++){
		f=0;
		for(k=8; k>=j; k--){
			if(num[k+1]<num[k]){
				temp = num[k+1];
				num[k+1] = num[k];
				num[k] = temp;
				f=1;
			}
		}
	if(!f)
		break;
	
	}
	for(n=0; n<10; n++)
		printf("%d\n", num[n]);
	return 0;
}
