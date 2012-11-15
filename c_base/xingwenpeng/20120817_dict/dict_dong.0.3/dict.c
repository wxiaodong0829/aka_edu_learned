/*************************************************************************
    > File Name: dict.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月17日 星期五 09时03分16秒
 ************************************************************************/

#include "dict.h"
void print_one_elem(dict_elem_t *word_p)
{
	int i;

	printf("#%s\n", word_p->key);
	for (i = 0; i < word_p->n_trans; i++)
		printf("%s ", word_p->trans[i]);
	printf("\n");
}

void print_data(dict_elem_t *head_p, int w_count)
{
	int i;
	for (i = 0; i < w_count; i++) {
		//printf("[%d]:\n", i+1);
		print_one_elem(&(head_p[i]));
	}
}


int get_elem_count(char *filename)
{
	FILE *fp;
	int ret = 0;
	char c;

	if ((fp = fopen(filename, "r")) == NULL) {
		perror("word_default.c  fopen: ");
		return -1;
	}
	while ((c = (char)fgetc(fp)) != EOF) 
		if (c == '#')
			ret++;
	fclose(fp);
	return ret;
}
void shell_sort(dict_elem_t *head_p, int l, int r)
{
	int i, j, gap;
	dict_elem_t tmp;
	for (gap = (r-l+1)/2; gap >= 1; gap /= 2)
		for (j = l + gap; j <= r; j++) {
			tmp = head_p[j];
			for (i = j - gap; i >= l && (strcmp(tmp.key, head_p[i].key) < 0); i -= gap)
				head_p[i+gap] = head_p[i];
			head_p[i+gap] = tmp;
		}
}
static dict_elem_t *binsearch(dict_elem_t *head_p, int w_count, char *key_word)
{
	int mid = 0, l = 0, r = w_count-1;

	while (l <= r) {
		mid = (l + r) / 2;
		if (strcmp(key_word, head_p[mid].key) < 0)
			r = mid - 1;
		else if (strcmp(key_word, head_p[mid].key) > 0)
			l = mid + 1;
		else 
			return &(head_p[mid]);
	}
	return NULL;
}

dict_elem_t *search(dict_elem_t *head_p, int w_count)
{
	dict_elem_t *elem_fund = NULL;
	char user_in[BUFSIZ] = "";
	char *tmp = NULL;
	int len = 0;

	while(1) {
		if ((tmp = fgets(user_in, BUFSIZ, stdin)) == NULL) {
			printf("wd_search() fgers error");
			return (dict_elem_t *)2;
		}
		if (strcmp(tmp, "exit\n") == 0) //user exit
			return (dict_elem_t *)1;

		len = strlen(user_in);

		if (user_in[len-1] == '\n')
			user_in[len-1] = '\0';

		if ((elem_fund = binsearch(head_p, w_count, user_in)) == NULL) {
			printf("no found it\n");
			//add_new_key; elem_fund = add_new_key(user_in, filename_user);
			//
			return NULL;
		}
		return elem_fund;
	}

}
void distory(dict_elem_t *head_p, int w_count)
{
	int i, j;
	for (i = 0; i < w_count; i++) {
		free(head_p[i].key);
		for (j = 0; j < head_p[i].n_trans; j++)
			free(head_p[i].trans[j]);
		free(head_p[i].trans);
	}
	free(head_p);
}

