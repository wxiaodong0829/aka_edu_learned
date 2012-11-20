#include<stdio.h>
#include<stdlib.h>
char *myitoa(int n,char *strp)
{
  int i, j, flag;
  char tmp;
  char *table = "0123456789";
  if((flag = n) <0)
    n = -n;
  i = 0;
  do{
    strp[i++] = table[n%10];
  }while(n/=10);
  if(flag<0)
    strp[i++]='-';
  strp[i] = '\0';
  for(--i,j=0; i >= j; i--,j++)
  {
    tmp =  strp[i]; strp[i] = strp[j];
    strp[j] = tmp;
  }
  return strp;
}
int main()
{
  char *strp = malloc(100);
  int n;
  printf("please input n:");
  scanf("%d\n",&n);
  printf("%s\n",myitoa(n,strp));
  return 0;
}
