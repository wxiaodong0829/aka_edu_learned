/*************************************************************************
    > File Name: main.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月16日 星期四 16时32分42秒
 ************************************************************************/

#include <stdio.h>
/******************************************wd.h***/
#ifndef WORD_DEFAULT_H_
#define WORD_DEFAULT_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <error.h>

//#include "debug.h"
/********************
 *
 *  search from txt famot
 *
 * ****************/
typedef struct dict_elem {
	char *key;
	int n_trans;
	char **trans;
} dict_elem_t;

#endif 



/****************main.c***********************/
static void print_one_elem(dict_elem_t *word_p)
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

static void wd_remove_first(char *buf, int len)
{
	int i;
	for (i = 1; i < len; i++)
		buf[i-1] = buf[i];

	buf[i-1] = '\0';
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

	for (tmp = buf, i = 0; (tmp = strtok(tmp, "@")) == NULL; i++, tmp = NULL) {
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
static void shell_sort(dict_elem_t *head_p, int l, int r)
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
static void distory(dict_elem_t *head_p, int w_count)
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

void wd()
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
		if (elem_fund == NULL)
			continue;
		else if ((unsigned)elem_fund == 1)
			exit(0);
		else if ((unsigned)elem_fund == 2) {
			printf("error");
			exit(-1);
		} else {
			print_one_elem(elem_fund);
		}
	}
		
	distory(head_p, total);
}
static void *bd_fwrite(dict_elem_t *b_head_p, int w_count, char *binary_file_name)
{
	FILE *fbp;
	int i, j;
	int len;

	if ((fbp = fopen(binary_file_name, "wb")) == NULL) {
		perror("bd_fwrite at fopen:");
		return NULL;
	}

	fwrite(&w_count, sizeof(w_count), 1, fbp); //word_count;

	for (i = 0; i < w_count; i++) { //word info
		len = strlen(b_head_p[i].key); 
		fwrite(&len, sizeof(len), 1, fbp);

		fwrite(b_head_p[i].key, len, 1, fbp);

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
static dict_elem_t *bd_fread(FILE *fbp, dict_elem_t *b_head_p, int w_count)
{
	int  i, j;
	int len_tran_one;
	int malloc_len;
	int len;

	for (i = 0; i < w_count; i++) {
		fread(&len, sizeof(len), 1, fbp);

		b_head_p[i].key = malloc(len + 1);
		fread(b_head_p[i].key, len, 1, fbp);
		b_head_p[i].key[len - 1] = '\0';

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

int main(int argc, char *argv[])
{
	dict_elem_t *head_p;
	int total;
	char *value;

	dict_elem_t *elem_fund;

	FILE *fp_b;

	switch(argc) {
		case 2: //
			if (strcmp(argv[1], "-test1") == 0) {
				wd();
			} else if (strcmp(argv[1], "-test2") == 0){
				if ((fp_b = fopen("dict.dat","rb")) == NULL) {
						total = get_elem_count("dict.txt");
						head_p = malloc(total * sizeof(*head_p));
						head_p = read_to_mem_from_txt("dict.txt", head_p, total);

						if ((value = bd_fwrite(head_p, total, "dict.dat")) == NULL)
						{
							printf("error in bd_fwrite() \n");
							return NULL;
						}

				} else {
					fread(&total, sizeof(total), 1, fp_b);
					head_p = malloc(total * sizeof(*head_p));
					head_p = bd_fread(head_p, total);
				}
				print_data(head_p, total);
			} else {
				printf("please input right args");
				return -1;
			}
			break;
		case 4:
			break;
		default :
				printf("please input right args");
				return -1;
	}



	return 0;
}
