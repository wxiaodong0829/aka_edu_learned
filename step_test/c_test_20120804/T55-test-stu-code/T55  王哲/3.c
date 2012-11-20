#include <stdio.h>



int main()
{
	int i, j, k, l, temp, arr[5][5];
	for(i=0; i<5; i++){
		for(j=0; j<5; j++)
			  arr[i][j] = rand()%100;
	}
	for(i=0; i<5; i++){
		for(j=0; j<4; j++){
			k = j;
		for(l=j+1; l<5; l++)
			if(arr[i][k] > arr[i][l])
				k = l;
		if(k != j){
			temp = arr[i][j];
			arr[i][j] = arr[i][k];
			arr[i][k] = temp;
		}
	}
	}
	
	for(i=0; i<5; i++){
		for(j=0; j<5; j++)
	printf("%d ",arr[i][j]);
		printf("\n");
	}

	return 0;
}
