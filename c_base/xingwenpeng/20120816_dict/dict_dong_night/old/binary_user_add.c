/*************************************************************************
    > File Name: binary_default.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月14日 星期二 19时42分32秒
 ************************************************************************/

#include "binary_default.h"
#include "word_default.h"

/*********************************
 * DEBUG table
 * DEBUGB1 test read_from_txt()
 *
 *	wd_print_data(head_p, w_count); //整合为一个函数
 * DEBUGB2  bd_copy_from_wd()
 *
 * bd_shell_sort()  能不能和 wd_  类的合并为一个。
 * bd_search()
 * bd_binsearch()
 *
 *
 *
 *******************************/
#if 1
static dict_bin_t *bd_no_binary(char *txt_file_name, char *binary_name, int *w_count);
static dict_bin_t *bd_have_binary(char *binary_file_name, int *w_count);
void bd_print_data(dict_bin_t *b_head_p, int w_count);
//static int bd_get_elem_count(char *filename);

//static dict_bin_t * bd_read_elem_from_bin(FILE *fp, dict_bin_t *head_p, int w_count);

//static dict_bin_t * bd_read_key(FILE *fp, dict_bin_t *word_p);

//static dict_bin_t * bd_read_trans(FILE *fp, dict_bin_t *word_p);

//static void bd_shell_sort(dict_elem_t *head_p, int l, int r);

//static void bd_binsearch(dict_elem_t *head_p, char *key_word);

dict_bin_t * bd_write_binary(dict_bin_t *head_p);

#endif

static void bd_shell_sort(dict_bin_t *head_p, int l, int r)
{
	int i, j, gap;
	dict_bin_t tmp;
	for (gap = (r-l+1)/2; gap >= 1; gap /= 2)
		for (j = l + gap; j <= r; j++) {
			tmp = head_p[j];
			for (i = j - gap; i >= l && (strcmp(tmp.key, head_p[i].key) < 0); i -= gap)
				head_p[i+gap] = head_p[i];
			head_p[i+gap] = tmp;
		}
}
static dict_bin_t *bd_binsearch(dict_bin_t *head_p, int w_count, char *key_word)
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
static dict_bin_t *bd_search(dict_bin_t *head_p, int w_count)
{
	dict_bin_t *elem_fund = NULL;
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

	if ((elem_fund = bd_binsearch(head_p, w_count, user_in)) == NULL) {
		printf("no found it\n");
		//add_new_key; elem_fund = add_new_key(user_in, filename_user);
		//
		return NULL;
	}

	return elem_fund;
}


static	void bd_copy_from_wd(dict_bin_t *b_head_p, dict_elem_t *head_p, int w_count)
{
	int i;

	for (i = 0; i < w_count; i++) {
		b_head_p[i].key_len = strlen(head_p[i].key);
		b_head_p[i].key = head_p[i].key;
		b_head_p[i].n_trans = head_p[i].n_trans;
		b_head_p[i].trans = head_p[i].trans;
	}
}
static void bd_print_one_elem(dict_bin_t *word_p)
{
	int i;

	printf("#%s\n", word_p->key);
	for (i = 0; i < word_p->n_trans; i++)
		printf("%s ", word_p->trans[i]);
	printf("\n");
}
void bd_print_data(dict_bin_t *b_head_p, int w_count)
{
	int i;
	for (i = 0; i < w_count; i++)
		bd_print_one_elem(&(b_head_p[i]));
	
}
static void bd_distory(dict_bin_t *head_p, int w_count)
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

static void *bd_fwrite(dict_bin_t *b_head_p, int w_count, char *binary_file_name)
{
	FILE *fbp;
	int i, j;
	int len;

	if ((fbp = fopen(binary_file_name, "wb")) == NULL) {
		perror("bd_fwrite at fopen:");
		return NULL;
	}
#if DEBUGB4
	fwrite("abcdefg", 7, 1, fbp);
#endif 

	fwrite(&w_count, sizeof(w_count), 1, fbp); //word_count;

	for (i = 0; i < w_count; i++) { //word info
		fwrite(&(b_head_p[i].key_len), sizeof(b_head_p[i].key_len), 1, fbp);
		PRINT_P(b_head_p[i].key);
		PRINT_P(&b_head_p[i].key);
		PRINT_S(b_head_p[i].key);
		PRINT(b_head_p[i].key_len);
		fwrite(b_head_p[i].key, b_head_p[i].key_len, 1, fbp);

		fwrite(&(b_head_p[i].n_trans), sizeof(b_head_p[i].n_trans), 1, fbp);

		for (j = 0; j < b_head_p[i].n_trans; j++) {
			len = strlen(b_head_p[i].trans[j]);
			fwrite(&(len), sizeof(len), 1, fbp);
			fwrite(b_head_p[i].trans[j], len, 1, fbp);
		}
	}

	fclose(fbp);
	return (void *) 1;
}

static dict_bin_t *bd_no_binary(char *txt_file_name, char *binary_file_name , int *w_count)
{
	dict_elem_t *head_p = NULL;
	dict_bin_t  *b_head_p = NULL;
	void *value;

	*w_count = wd_get_elem_count(txt_file_name);
	if (w_count < 0)
		return (void *)NULL;
	PRINT(*w_count);
	printf("%d\n", *w_count);

	head_p = malloc((*w_count) * sizeof(*head_p));

	PRINT_P(head_p);
	PRINT_P(&head_p);
	PRINT((*w_count) * sizeof(*head_p));

	if ((head_p = wd_read_elem_from_txt(txt_file_name, head_p, *w_count)) == NULL) {
		printf("wd_word_default() wd_read_elem_from_txt() is error\n");
		return NULL;
	}
#if DEBUGB1
//	wd_print_data(head_p, *w_count);
#endif

	b_head_p = malloc((*w_count) * sizeof(*b_head_p));
//#if DEBUGB1
//	printf("%d %p\n", (*w_count)*sizeof(*b_head_p), b_head_p);
//#endif
//#if DEBUGB2
//	printf("debug bd_copy_from_wd\n");
	bd_copy_from_wd(b_head_p, head_p, *w_count);

	free(head_p);

//	bd_print_data(b_head_p, *w_count);
//#endif
	if ((value = bd_fwrite(b_head_p, *w_count, binary_file_name)) == NULL)
	{
		printf("error in bd_no_binary \n");
		return NULL;
	}

#if DEBUGB3
#endif
#if 0
#endif 
	
	return b_head_p;
}
static dict_bin_t *bd_have_binary(char *binary_file_name, int *w_count)
{
	FILE *fbp;
	dict_bin_t *b_head_p;
	int  i, j;
	int len_tran_one;
	int malloc_len;

	if ((fbp = fopen(binary_file_name, "rb")) == NULL) {
		perror("bd_have_binary() fopen : ");
		return NULL;
	}

	fread(w_count, sizeof(*w_count), 1, fbp);

	b_head_p = malloc((*w_count) * sizeof(*b_head_p));

	for (i = 0; i < *w_count; i++) {
		fread(&b_head_p[i].key_len, sizeof(b_head_p[i].key_len), 1, fbp);

		malloc_len = sizeof(*(b_head_p[i].key)) * (b_head_p[i].key_len) + 1;
		b_head_p[i].key = malloc(malloc_len);
		fread(b_head_p[i].key, b_head_p[i].key_len, 1, fbp);
		b_head_p[i].key[malloc_len - 1] = '\0';

		fread(&b_head_p[i].n_trans, sizeof(b_head_p[i].n_trans), 1, fbp);
		b_head_p[i].trans = malloc(b_head_p[i].n_trans * sizeof(*(b_head_p[i].trans)));

		for (j = 0; j < b_head_p[i].n_trans; j++) {
			fread(&len_tran_one, sizeof(len_tran_one), 1, fbp);
			malloc_len = sizeof(*(b_head_p[i].trans[j])) * len_tran_one + 1;
			b_head_p[i].trans[j] = malloc(malloc_len);
			fread(b_head_p[i].trans[j], len_tran_one, 1, fbp);
			b_head_p[i].trans[j][malloc_len - 1] = '\0';
		}

	}
	

	return b_head_p;

}

void *bd_binary_default(char *txt_file_name, char *binary_file_name)
{
	FILE *fbp;
	dict_bin_t *b_head_p; //out from bd_no_binary() or bd_have_binary()
	int w_count = 0;
	int i;
	dict_bin_t *elem_fund;

	if ((fbp = fopen(binary_file_name, "r")) == NULL) {
		b_head_p = bd_no_binary(txt_file_name, binary_file_name, &w_count);
	} else 
		b_head_p = bd_have_binary(binary_file_name, &w_count);
	if (b_head_p == NULL) {
		printf("read binary in bd_binary_default() error\n");
		exit(-1);
	}

//	bd_print_data(b_head_p, w_count);

#if DEBUGB1
	printf("%p\n", b_head_p);
#endif
	//shell
	bd_shell_sort(b_head_p, 0, w_count - 1);
	
	//search
	printf("Welcome enjoy this dictionary soft\n");
	for (;;) {
//		wd_print_data(head_p, w_count);
		elem_fund = bd_search(b_head_p, w_count);
		if (elem_fund == NULL)
			continue;
		for (i = 0; i < elem_fund->n_trans; i++) {
			printf("%s\n", elem_fund->trans[i]);
		}
	}
	
	bd_distory(b_head_p, w_count);

	return b_head_p;
}
