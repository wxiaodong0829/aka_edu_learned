/*************************************************************************
    > File Name: word_default.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月17日 星期五 08时33分48秒
 ************************************************************************/

#include "word_default.h"


static void wd_remove_first(char *buf, int len)
{
	int i;
	for (i = 1; i < len; i++)
		buf[i-1] = buf[i];

	buf[i-1] = '\0';
}
static char * wd_read_key(FILE *fp, dict_elem_t *word_p)
// return EOF or malloc of word_p->key 
{
	//char buf[BUFSIZ/10];
	char buf[BUFSIZ];
	char *ret;
	int len;
	if ((ret = fgets(buf, BUFSIZ, fp)) == NULL)
		return NULL;	//EOF
	len = strlen(buf);
	if (buf[len-1] == '\n') {
		buf[len-1] = '\0';
		wd_remove_first(buf, len-1);
		len = strlen(buf);
		word_p->key = malloc(len + 1);
	} else {
		wd_remove_first(buf, len);
		len = strlen(buf);
		word_p->key = malloc(len + 1);
	}
	
	strncpy(word_p->key, buf, len);


	return word_p->key;
}
static char * wd_read_trans(FILE *fp, dict_elem_t *word_p)
//return EOF
{
	char *tmp;
	//char buf[BUFSIZ/10];
	char buf[BUFSIZ];
	int len;
	int n_trans = 1;
	int i;

	if ((tmp = fgets(buf, BUFSIZ, fp)) == NULL)
		return NULL;	//EOF
	len = strlen(buf);
	if (buf[len-1] == '\n')
		buf[len-1] = '\0';

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '@' && buf[i+1] != '@' && buf[i+1] != '\0')
			n_trans++;
	word_p->n_trans = n_trans;

	word_p->trans = malloc(sizeof(char *) * n_trans);

	for (tmp = buf, i = 0; (tmp = strtok(tmp, "@")) != NULL; i++, tmp = NULL) {
		len = strlen(tmp);
		word_p->trans[i] = malloc(len + 1);
		strncpy(word_p->trans[i], tmp, len);
	}

	return (char *)1;
}
dict_elem_t *read_to_mem_from_txt(char *filename, dict_elem_t *head_p, int w_count)
{
	int i = 0;
	FILE *fp;
	char *ret;
	if ((fp = fopen(filename, "r")) == NULL) {
		perror("wd_read_elem_from_txt fopen: ");
		return NULL;
	}
	while(i < w_count) {
		if ((ret = (char *)wd_read_key(fp, &(head_p[i]))) == NULL)
			break;
		if ((ret = (char *)wd_read_trans(fp, &(head_p[i]))) == NULL)
			break;
		i++;
	}
	fclose(fp);

	//print_data(head_p, w_count);
	return head_p;
}
char *word_default(void)
{
	dict_elem_t *head_p;
	int total;

	dict_elem_t *elem_fund;
	total = get_elem_count("dict.txt");
			
	head_p = malloc(total * sizeof(*head_p));

	head_p = read_to_mem_from_txt("dict.txt", head_p, total);
	shell_sort(head_p, 0, total-1);

	printf("\n\t\t\tWelcome enjoy this dictionary\n\n");
	printf("input you word ,exit is quit...  \n");
	while(1) {
		elem_fund = search(head_p, total); //退出，说明没找到，继续找
		if (elem_fund == NULL) {
			//add_ne
			continue;
		}
		else if ((unsigned)elem_fund == 1) {
			distory(head_p, total);
			return (char *) 1;
		} else if ((unsigned)elem_fund == 2) {
			puts("error");
			distory(head_p, total);
			return (char *)2;
		} else {
			print_one_elem(elem_fund);
		}
	}
		
}

