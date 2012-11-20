#include<stdio.h>
#include<string.h>

char str[13] = "olympicgames";
int finmax()
{
    int max, i, flag;
    char t[15];
    strcpy(t, str);
    max = (int)t[0];
    for(i=0; t[i]!='\0'; i++)
    {
        if(t[i] >= max)
        {
            max = t[i];
            flag = i;
        }
    }
    printf("%c\t%d\n",(char)max, flag);
    return flag;
}
int main()
{
    int j; char tmp;
    int flag = finmax();
    tmp = str[flag];
    for(j = flag; j >0 ; j--)
    {
        str[j] = str[j-1];
    }
    str[0] = tmp;
        printf("%s\n",str);
    return 0;



}
