/*************************************************************************
    > File Name: binary_default.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月17日 星期五 09时12分57秒
 ************************************************************************/
#include "binary_default.h"


void *bd_fwrite(dict_elem_t *b_head_p, int w_count, char *binary_file_name)
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

dict_elem_t *bd_fread(FILE *fbp, dict_elem_t *b_head_p, int w_count)
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
char  *binary_default(void)
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
			puts("error in bd_fwrite() ");
			return (char *) 2;
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
		else if ((unsigned)elem_fund == 1) {
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
