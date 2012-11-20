#include<stdio.h>
int add(int a,int b)
{
	return a+b;
}
int sub(int a,int b)
{
	return a-b;
}
int chen(int a,int b)
{
	return a*b;
}
double chu(int  a,int b)
{
	if(b==0)
	{
		printf("error\n");
		return 0;
	}
	else
	return (double)(a/b);
}

int main(void)
{
	int m,n,a=0;
	char  t;
	int (*f1)(int,int)=add;
	int (*f2)(int,int)=sub;
	int (*f3)(int , int)=chen;
	double (*f4)(int,int)=chu;
	do
	{
		scanf("%c",&t);
		switch(t)
		{
		case '+':{scanf("%d %d",&m,&n);
				  printf("%d\n",f1(m,n));			
				 } 
		case '-':{
					scanf("%d %d",&m,&n);
					printf("%d\n",f2(m,n));	
				 }
		case '*':{
					scanf("%d %d",&m,&n);
					printf("%d\n",f3(m,n));
			     }
		case '/':{
		
				 	scanf("%d %d",&m,&n);
					printf("%f\n",f4(m,n));
				 }
		}
	}while(t!='#');
//	int  (*f1)(int a,int b)=add;
//	int (*f2)(int a , int b)=sub;
//	printf("%d\n",f1(m,n));


	return 0;
}
