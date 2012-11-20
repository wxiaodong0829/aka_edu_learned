#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define N 11
int a[N];
void init(int l,int r)
{
	int i;
	srand(time(NULL));
	for(i=l;i<=r;i++)
	a[i]=rand()%100;
}
void show (int l,int r)
{
	int i;
	for(i=0;i<l;i++) printf("  ");
	for(i=l;i<=r;i++) printf("%3d",a[i]);
	printf("\n");
}
void swap(int i,int j){int tmp =a[i];a[i]=a[j];a[j]=tmp;}
int partition(int l,int r)
{
	int i,j;
	int k=rand()%(r-l+1)+l;
	swap(l,k);
	for(j=l,i=j+1;i<=r;i++)
	if(a[i]<a[l])
	swap(i,++j);
	swap(l,j);
	show(l,r);
	return j;
}
void sort (int l,int r)
{
	if(l>=r)return;
	int k=partition(l,r);
	sort(l,k-1);
	sort(k+1,r);

}
int main()
{
	init(0,N-1);
	show(0,N-1);
	sort(0,N-1);
	show(0,N-1);
	return 0;

}















