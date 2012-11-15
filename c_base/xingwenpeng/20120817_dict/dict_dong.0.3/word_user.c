/*************************************************************************
    > File Name: word_user.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月17日 星期五 09时10分42秒
 ************************************************************************/

#include "word_user.h"

static void add_new_key(char *filename_user)
{
	char key[BUFSIZ];
	char trans[BUFSIZ];
	char tmp[BUFSIZ/10];
	char c[BUFSIZ/50];
	FILE *fp;
	int len;

	printf("Are you add a new word (y / n):\n");
	fgets(c, BUFSIZ/50, stdin);
	if (strcmp(c, "y\n") == 0 || strcmp(c, "Y\n") == 0) {
		fp = fopen(filename_user, "a+");
		printf("word : \n");
		fgets(key, BUFSIZ, stdin);
		len = strlen(key);

		printf("Trans (end by '#'):\n");
		strncat(trans,"Trans:", strlen("Trans:"));
		fgets(tmp, BUFSIZ/10, stdin);
		len = strlen(tmp);
		if (tmp[len - 1] == '\n')
			tmp[len - 1] = '\0';
		strncat(trans, tmp, strlen(tmp));
		while(strcmp(fgets(tmp, BUFSIZ/10, stdin), "#\n") != 0) {
			len = strlen(tmp);
			if (tmp[len - 1] == '\n')
				tmp[len - 1] = '\0';
			strncat(trans, "@", strlen("@"));
			strncat(trans, tmp, strlen(tmp));
		}
		fwrite("#", strlen("#"), 1, fp);
		fwrite(key, strlen(key), 1, fp);
		fwrite(trans, strlen(trans), 1, fp);
		fwrite("\n", strlen("\n"), 1, fp);

		fclose(fp);
	}
}
char *word_user(char *filename_user)
//当添加一个词条后，必须重新开始，才能再次加入查找范围
{
	dict_elem_t *head_p;
	int total;
	int total_d;
	int total_user;

	dict_elem_t *elem_fund;
	total_d = get_elem_count("dict.txt");
	total_user = get_elem_count(filename_user);

	if (total_user == -1) {
		total = total_d;
		head_p = malloc(total * sizeof(*head_p));
		head_p = read_to_mem_from_txt("dict.txt", head_p, total);
	} else {
		total = total_d + total_user;
		head_p = malloc(total * sizeof(*head_p));
		head_p = read_to_mem_from_txt("dict.txt", head_p, total_d);
		read_to_mem_from_txt(filename_user, &(head_p[total_d]), total_user);
	}
	shell_sort(head_p, 0, total-1);

	printf("\n\t\t\tWelcome enjoy this dictionary\n\n");
	printf("input you word ,exit is quit...  \n");
	for (;;) {
		elem_fund = search(head_p, total); //退出，说明没找到，继续找
		if (elem_fund == NULL) {
			add_new_key(filename_user);
			continue;
		} else if ((unsigned)elem_fund == 1) {
			distory(head_p, total);
			return (char *) 1;
		} else if ((unsigned)elem_fund == 2) {
			puts("error");
			distory(head_p, total);
			return (char *) 2;
		} else {
			print_one_elem(elem_fund);
		}
	}
		
}


