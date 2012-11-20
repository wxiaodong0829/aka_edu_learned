#include <stdio.h>

int main()
{
	int arr[5][5];
	int a[30];

	int i, j, k = 0, l = 0, temp;
	for(i=0; i<5; i++){
		for(j=0; j<5; j++)               
			arr[i][j] = rand()%100;
	}
		for(i=0; i<5; i++){
			for(j=0; j<5; j++) 
				a[k++] = arr[i][j];
	}



	for(i=0; i<25; i++){
		k = i;
		for(j=i+1; j<=25; j++)
			if(a[k] > a[j])
				k = j;
		if(k != i){
			temp = a[i];
			a[i] = a[k];
			a[k] = temp;
		}
	}
		for(i=0;i<25;i++)
			printf("%d ", a[i]);

		
		for(i=0; i<5; i++){
			for(j=0; j<5;l++, j++) 
			arr[i][j] = a[l];
		}
	
	for(i=0; i<5; i++){
		for(j=0; j<5; j++)
		printf("%d ",arr[i][j]);
		printf("\n");
	}


	return 0;
}
