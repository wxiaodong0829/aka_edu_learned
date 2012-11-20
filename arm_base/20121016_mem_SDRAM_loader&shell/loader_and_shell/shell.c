/*************************************************************************
	> File Name: shell.c
	> Author: wxiaodong
	> Mail  : wxiaodong0829@163.com 
	> 自由  谐作   创造   沟通
	> Created Time: 2012年10月16日 星期二 13时53分08秒
 ************************************************************************/

#include "shell.h"
#include "myxmodem.h"
#define BUFSIZE 256

void cmdline(char * str);
void shell(void)
{
	char str[BUFSIZE];
	while (1) {
		my_printf("tiny210# ");
		my_gets(str);
		cmdline(str);
	}
}

int my_strcmp(const char *cmp, const char *s)
{
	int i;
	for (i = 0; cmp[i]; i++) {
		if (s[i] == '\0')
			return -1;
		if (cmp[i] != s[i])
			return -1;
	}
	if (s[i])
		return -1;
	return 0;
}

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
void help()
{
	my_printf("help         list the commond of bootloader\n");
	my_printf("version      the bootloader's version info\n");
}
void go(int argc, char *argv[])
{
	unsigned int start;
	if (argc < 2) {
		my_printf("go 0x22000000\n");
		return ;
	}
	//start = atox(argv[1]);
	start = 0x22000000;
	((void(*)(void))start)();

}

void cmdline(char * str)
{
	int argc;
	char *argv[10];
	argc = parse(str, argv);
	//
	my_printf("cmp = %s\n", argv[0]);

	if (my_strcmp(argv[0], "help") == 0) {
		help();
	} else if (my_strcmp(argv[0], "loadb")) {
		loadx(argc, argv);
	} else if (my_strcmp(argv[0], "go")) {
		go(argc, argv);
	} else {//if (my_strcmp()) {
		my_printf("cmd not fund!\n");
	}
}

