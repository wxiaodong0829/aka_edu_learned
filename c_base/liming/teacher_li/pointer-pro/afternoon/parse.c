#include <stdio.h>
#if 0
int parse(char * buf, char * argv[])
{
    int n=0;
    char * p;
    for (p = buf; p=strtok(p, " "); p=NULL, n++)
        argv[n]=p;
    argv[n]=p;
    return n;
}
#else
int parse(char * buf, char * argv[])
{
    int n=0;
    int argc = 0;
    while (buf[n]) {
        if (buf[n]==' ')
            while (buf[++n]==' ');
        argv[argc] = &buf[n];
        while (buf[++n]!=' ');
        buf[n]='\0';
        argc++;
        n++;
    }
    argv[argc]=NULL;
    return argc;
}
#endif

int parse_2(char *buf, char *argv[])
{
    int i;
    int flag = 0;
    int argc = 0;
    for(i = 0; buf[i] != '\0'; i++)
    {
        if(buf[i] != ' ' && flag == 0)
        {
            argv[argc] = &buf[i];
            flag = 1;
            argc++;
        }
        else if(buf[i] == ' ' && flag == 1)
        {
            buf[i] = '\0';
            flag = 0;
        }
    }
    return argc;
}
int main(void)
{
    char buf[32] = {"   ./a.out 123  567  9"};
    int argc;
    char * argv[10];
    int i;

   // argc = parse(buf, argv);
    argc = parse_2(buf, argv);

    
    for (i = 0; i < argc; i++)
        printf("argv[%d] = <%s>\n", i, argv[i]);
    
    return 0;
}
