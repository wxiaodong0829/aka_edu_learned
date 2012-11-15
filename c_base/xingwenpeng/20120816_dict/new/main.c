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

/**************************bu.h***********/
#define LEN 20

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
		if (elem_fund == NULL) {
			//add_ne
			continue;
		}
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
		b_head_p[i].key[len] = '\0';

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

void bd()
{
	dict_elem_t *head_p;
	dict_elem_t *elem_fund;
	int total;
	
	FILE *fp_b;
	char *value;
			
	if ((fp_b = fopen("dict.dat","rb")) == NULL) {
		total = get_elem_count("dict.txt");
		head_p = malloc(total * sizeof(*head_p));
		head_p = read_to_mem_from_txt("dict.txt", head_p, total);

		if ((value = bd_fwrite(head_p, total, "dict.dat")) == NULL)
		{
			printf("error in bd_fwrite() \n");
			return ;
		}

	} else {
		fread(&total, sizeof(total), 1, fp_b);
		head_p = malloc(total * sizeof(*head_p));
		head_p = bd_fread(fp_b, head_p, total);
	}
//	print_data(head_p, total);

	shell_sort(head_p, 0, total-1);

	printf("\n\t\t\tWelcome enjoy this dictionary\n\n");
	printf("input you word ,exit is quit...  \n");
	while(1) {
		elem_fund = search(head_p, total); //1: 退出，NULL: 没找到,继续找  elem_fund:找到
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
char * search_and_add_wu(char *filename_user)
{
	dict_elem_t *head_p;
	dict_elem_t *elem_fund;
	int total = get_elem_count(filename_user);

	head_p = malloc(total * sizeof(*head_p));

	head_p = read_to_mem_from_txt(filename_user, head_p, total);
	shell_sort(head_p, 0, total-1);
}

void add_new_key(char *filename_user)
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
	}
	fclose(fp);
}
void wu(char *filename_user)
//当添加一个词条后，必须重新开始，才能再次加入查找范围
{
	dict_elem_t *head_p;
	dict_elem_t *head_user_p;
	int total;
	int total_d;
	int total_user;
	char *ret;

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
		} else if ((unsigned)elem_fund == 1)
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

void add_new_key_bin(char *filename_user)
{
	char key[BUFSIZ];
	char trans[BUFSIZ];
	char tmp[LEN][BUFSIZ/50];
	int tran_len[LEN];
	int n_trans = 0;
	char c[BUFSIZ/50];
	FILE *fp;
	int len;
	int total = 0;
	int i, j;

	printf("Are you add a new word (y / n):\n");
	fgets(c, BUFSIZ/50, stdin);
	if (strcmp(c, "y\n") == 0 || strcmp(c, "Y\n") == 0) {
		fp = fopen(filename_user, "a+");

		rewind(fp);
		fread(&total, sizeof(total), 1, fp);
		total++;
		fseek(fp, -sizeof(total), SEEK_CUR);
		fwrite(&total, sizeof(total), 1, fp);
		fseek(fp, 0, SEEK_END);

		printf("word : \n");
		fgets(key, BUFSIZ, stdin);
		len = strlen(key);
		if (key[len - 1] == '\n')
			key[len - 1] = '\0';
		len = strlen(key);
		fwrite(&len, sizeof(len), 1, fp);
		fwrite(key, len, 1, fp);

		printf("Trans (end by '#'):\n");
		while(strcmp(fgets(tmp[i], BUFSIZ/50, stdin), "#\n") != 0) {
			tran_len[i] = strlen(tmp[i]);
			if (tmp[i][tran_len[i] - 1] == '\n')
				tmp[i][tran_len[i] - 1] = '\0';
			tran_len[i] = strlen(tmp[i]);
			i++;
		}
		fwrite(&i, sizeof(i), 1, fp);
		for (j = 0; j < i; j++) {
			fwrite(&tran_len[j], sizeof(tran_len[j]), 1, fp);
			fwrite(tmp[j], tran_len[j], 1, fp);
		}

		fclose(fp);
	}
}
void bu(char *filename_user)
{
	dict_elem_t *head_p;
	dict_elem_t *elem_fund;
	int total;
	int total_d;
	int total_user;
	
	FILE *fp_b;
	FILE *fp_u;
	char *value;
			
	if ((fp_b = fopen("dict.dat","rb")) == NULL) { //bug ----->>>  当用户插入新词后删除 dict.dat 则接下来的第一次打开时,不能读用户给的 dict_user.dat  再次打开时才能读入 dict_user.dat
		total = get_elem_count("dict.txt");
		head_p = malloc(total * sizeof(*head_p));
		head_p = read_to_mem_from_txt("dict.txt", head_p, total);

		if ((value = bd_fwrite(head_p, total, "dict.dat")) == NULL)
		{
			printf("error in bd_fwrite() \n");
			return ;
		}

	} else {
		if ((fp_u = fopen(filename_user, "rb")) == NULL) {
			fread(&total, sizeof(total), 1, fp_b);
			head_p = malloc(total * sizeof(*head_p));
			head_p = bd_fread(fp_b, head_p, total);
		} else {
			fread(&total_d, sizeof(total_d), 1, fp_b);
			fread(&total_user, sizeof(total_user), 1, fp_u);
			total = total_d + total_user;
			head_p = malloc(total * sizeof(*head_p));
			head_p = bd_fread(fp_b, head_p, total_d);
			bd_fread(fp_u, &(head_p[total_d]), total_user);

			fclose(fp_u);
		}
		fclose(fp_b);
	}
//	print_data(head_p, total);

	shell_sort(head_p, 0, total-1);

	printf("\n\t\t\tWelcome enjoy this dictionary\n\n");
	printf("input you word ,exit is quit...  \n");
	while(1) {
		elem_fund = search(head_p, total); //1: 退出，NULL: 没找到,继续找  elem_fund:找到
		if (elem_fund == NULL) {
			add_new_key_bin(filename_user);
			continue;
		} else if ((unsigned)elem_fund == 1)
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
				bd();
			} else {
				printf("please input right args\n");
				return -1;
			}
			break;
		case 4:
			if (strcmp(argv[1], "-test1") == 0) {
				wu(argv[3]);

			} else if (strcmp(argv[1], "-test2") == 0){
				bu(argv[3]);
			} else {
				printf("please input right args\n");
				return -1;
			}
			break;
		default :
				printf("Please input right args\n");
				printf("Example:\n");
				printf("$ ./a.out -test1\n");
				printf("$ ./a.out -test2\n");
				printf("$ ./a.out -test1 -f dict_new.txt\n");
				printf("$ ./a.out -test2 -f dict_new.dat\n");
				return -1;
	}



	return 0;
}
