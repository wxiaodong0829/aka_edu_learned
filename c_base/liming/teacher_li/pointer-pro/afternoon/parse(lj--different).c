#include<stdio.h>
#include<stdlib.h>

int parse(char * buf, char *argv[])
{
		int argc = 0;
		int i;
		if(buf[0]!= ' ')
		{
				argv[0]= &buf[0];
				argc = 1;
		}
		for(i=1;buf[i] != '\0';i++){

		if(buf[i]!=' ' && (buf[i-1] == ' ' || buf[i-1] == '\0'))
		{		
				argv[argc] = &buf[i];
		        argc++; 	
		}
		else if(buf[i] == ' ' && buf[i-1]!=' ')
		{	
				buf[i] = '\0';
		} 
}
		return argc;
           
}


int main(void)
{
		char buf[32] = {" ./a.out    123 567 9"};
		int argc;
		char *argv[10];
		int i;

		argc = parse(buf, argv);
		for(i = 0; i<argc; i++)
	    printf("argv[%d] = <%s>\n", i, argv[i]);

		return 0;
}
