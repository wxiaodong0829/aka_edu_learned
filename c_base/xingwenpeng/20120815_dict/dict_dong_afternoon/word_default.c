/*************************************************************************
    > File Name: word_default.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月14日 星期二 19时18分46秒
 ************************************************************************/

#include "word_default.h"

#if 0
static int wd_get_elem_count(char *filename);

static dict_elem_t * wd_read_elem_from_txt(char *filename, dict_elem_t *head_p, int w_count);

static dict_elem_t * wd_read_key(FILE *fp, dict_elem_t *word_p);

static dict_elem_t * wd_read_trans(FILE *fp, dict_elem_t *word_p);


static void wd_shell_sort(dict_elem_t *head_p, int l, int r);

static void wd_binsearch(dict_elem_t *head_p, char *key_word);
#endif

static void wd_remove_first(char *buf, int len);


static int wd_get_elem_count(char *filename)
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
	PRINT(ret);
	return ret;
}
static void wd_print_one_elem(dict_elem_t *word_p)
{
	int i;

	printf("#%s\n", word_p->key);
	for (i = 0; i < word_p->n_trans; i++)
		printf("%s ", word_p->trans[i]);
	printf("\n");
}

static void wd_print_data(dict_elem_t *head_p, int w_count)
{
	int i;
	for (i = 0; i < w_count; i++) {
		//printf("[%d]:\n", i+1);
		wd_print_one_elem(&(head_p[i]));
	}
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

	PRINT_P(word_p->key);
	PRINT_S(word_p->key);

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
		if (buf[i] == '@')
			n_trans++;
	word_p->n_trans = n_trans;
	PRINT(n_trans);

	word_p->trans = malloc(sizeof(char *) * n_trans);

	for (tmp = buf, i = 0; tmp = strtok(tmp, "@"); i++, tmp = NULL) {
		len = strlen(tmp);
		word_p->trans[i] = malloc(len + 1);
		strncpy(word_p->trans[i], tmp, len);
		PRINT_P(word_p->trans[i]);
		PRINT_S(word_p->trans[i]);
	}

	return 1;
}

static void wd_shell_sort(dict_elem_t *head_p, int l, int r)
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

static dict_elem_t * wd_read_elem_from_txt(char *filename, dict_elem_t *head_p, int w_count)
{
	int i = 0, j;
	int len = 0;
	int n_trans;
	FILE *fp;
	char *ret;
	char *tmp;
	if ((fp = fopen(filename, "r")) == NULL) {
		perror("wd_read_elem_from_txt fopen: ");
		return NULL;
	}
	rewind(fp);
	//malloc of all dict.txt in memory.
#if DEBUG3
	char buf[BUFSIZ];
	while(fgets(buf, BUFSIZ, fp) != NULL) {
		if ( buf[0] == '#') {
			tmp = buf;
			len = strlen(buf);
			tmp[len-1] = '\0';
			wd_remove_first(tmp, len);
			len = strlen(tmp);
			head_p[i].key = malloc(len + 1);
			strncpy(head_p[i].key, tmp, len);

			fgets(buf, BUFSIZ, fp);

			len = strlen(buf);
			buf[len - 1] = '\0';
			n_trans = 1;
			for (j = 0; buf[j]; j++)
				if (buf[j] == '@')
					n_trans++;
			head_p[i].n_trans = n_trans;
			PRINT(n_trans);

			head_p[i].trans = malloc(sizeof(char *) * n_trans);

			for (tmp = buf, j = 0; tmp = strtok(tmp, "@"); j++, tmp = NULL) {
				len = strlen(tmp);
				head_p[i].trans[j] = malloc(len + 1);
				strncpy(head_p[i].trans[j], tmp, len);
			//	PRINT_P(head_p[i].trans[j]);
			//	PRINT_S(head_p[i].trans[j]);
			}

			i++;
		}
	}
#endif

#if 1
	while(i < w_count) {
		if ((ret = (char *)wd_read_key(fp, &(head_p[i]))) == NULL)
			break;
		if ((ret = (char *)wd_read_trans(fp, &(head_p[i]))) == NULL)
			break;
		i++;
	}
#endif

	fclose(fp);

#if DEBUG
	wd_print_data(head_p, w_count);
#endif

//	wd_shell_sort(head_p, 0, w_count-1);

#if DEBUG
	wd_print_data(head_p, w_count);
#endif
	
	return head_p;
}


static dict_elem_t *wd_binsearch(dict_elem_t *head_p, int w_count, char *key_word)
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

static void wd_remove_first(char *buf, int len)
{
	int i;
	for (i = 1; i < len; i++)
		buf[i-1] = buf[i];

	buf[i-1] = '\0';
}

static void wd_distory(dict_elem_t *head_p, int w_count)
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

static dict_elem_t *wd_search(dict_elem_t *head_p, int w_count)
{
	dict_elem_t *elem_fund = NULL;
	char user_in[BUFSIZ/10] = "";
	char *tmp = NULL;
	int len = 0;

	if ((tmp = fgets(user_in, BUFSIZ/10, stdin)) == NULL) {
		printf("wd_search() fgers error");
		return NULL;
	}
	if (strcmp(tmp, "exit\n") == 0) //user exit
		exit(0);

	len = strlen(user_in);

	if (user_in[len-1] == '\n')
		user_in[len-1] = '\0';
	PRINT_S("here");

	if ((elem_fund = wd_binsearch(head_p, w_count, user_in)) == NULL) {
		printf("no found it\n");
		//add_new_key; elem_fund = add_new_key(user_in, filename_user);
		//
		return NULL;
	}

	return elem_fund;
}

void * wd_word_default(char *filename)
{
	int i;
	dict_elem_t *head_p = NULL;
	dict_elem_t *elem_fund= NULL;
	int w_count = wd_get_elem_count(FILENAME);
	if (w_count < 0)
		return (void *)NULL;
	PRINT(w_count);
	printf("%d\n", w_count);
#if DEBUG2
	head_p = malloc(1000000000);
#endif
#if  DEBUG1
#else
	head_p = malloc(w_count * sizeof(*head_p));
	PRINT_P(head_p);
	PRINT_P(&head_p);
	PRINT(w_count * sizeof(*head_p));

	if ((head_p = wd_read_elem_from_txt(FILENAME, head_p, w_count)) == NULL)
		printf("wd_word_default() wd_read_elem_from_txt() is error\n");

	printf("Welcome enjoy this dictionary soft\n");
	for (;;) {
		wd_print_data(head_p, w_count);
		elem_fund = wd_search(head_p, w_count);
		if (elem_fund == NULL)
			continue;
		for (i = 0; i < elem_fund->n_trans; i++) {
			printf("%s\n", elem_fund->trans[i]);
		}
	}
	wd_distory(head_p, w_count);

#endif
}

