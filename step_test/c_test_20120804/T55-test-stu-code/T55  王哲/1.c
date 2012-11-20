#include <stdio.h>


int main()
{
	int n, i, j;
	//n=100;
	printf("write:");
	scanf("%d", &n);
	
	for(i=1; i<=n; i++){
		for(j=2;j<=i;j++){
			if(i%j == 0)
				break;
		}
			if(i == j)
				printf("%d\n",i);
		else
			continue;
		
	}

	return 0;
}
