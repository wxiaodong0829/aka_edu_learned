/*************************************************************************
    > File Name: binary_user.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月17日 星期五 09时17分33秒
 ************************************************************************/

#include "binary_user.h"
static void add_new_key_bin(char *filename_user)
{
	char key[BUFSIZ];
	char tmp[LEN][BUFSIZ/50];
	int tran_len[LEN];
	char c[BUFSIZ/50];
	FILE *fp;
	int len;
	int total = 0;
	int i = 0, j = 0;


	printf("Are you add a new word (y / n):\n");
	fgets(c, BUFSIZ/50, stdin);
	if (strcmp(c, "y\n") == 0 || strcmp(c, "Y\n") == 0) {
		if ((fp = fopen(filename_user, "rb+")) == NULL) {
			fp = fopen(filename_user, "ab+");
		}

		fseek(fp, 0, SEEK_SET);
		fread(&total, sizeof(total), 1, fp);
#if 0
		PRINT(total);
		total++;
		PRINT(total);
		total_test = total + 1;
		fseek(fp, -sizeof(total), SEEK_CUR);
		fwrite(&total_test, sizeof(total), 1, fp);
		fseek(fp, -sizeof(total), SEEK_CUR);
		fread(&total, sizeof(total), 1, fp);
		PRINT(total);
#else
		PRINT(total);
		total++;
		fseek(fp, -sizeof(total), SEEK_CUR);
		fwrite(&total, sizeof(total), 1, fp);
		fseek(fp, -sizeof(total), SEEK_CUR);
		fread(&total, sizeof(total), 1, fp);
		PRINT(total);

		fseek(fp, 0, SEEK_END);

#endif
		printf("word : \n");
		fgets(key, BUFSIZ, stdin);
		len = strlen(key);
		if (key[len - 1] == '\n')
			key[len - 1] = '\0';
		len = strlen(key);
		fwrite(&len, sizeof(len), 1, fp);
		fwrite(key, len, 1, fp);

		puts("Trans (end by '#'):\n");
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

#if DEBUG == 1
		fseek(fp, 0, SEEK_SET);
		fread(&total, sizeof(total), 1, fp);
		PRINT(total);
#endif

		fclose(fp);
	}
}
char *binary_user(char *filename_user)
{
	dict_elem_t *head_p;
	dict_elem_t *elem_fund;
	int total;
	int total_d;
	int total_user;
	
	FILE *fp_b;
	FILE *fp_u;
	char *value;

	//bug ----->>>  当用户插入新词后删除 dict.dat 则接下来的第一次打开时,
	//不能读用户给的 dict_user.dat  再次打开时才能读入 dict_user.dat
	if ((fp_b = fopen("dict.dat","rb")) == NULL) { 
		total = get_elem_count("dict.txt");
		head_p = malloc(total * sizeof(*head_p));
		head_p = read_to_mem_from_txt("dict.txt", head_p, total);

		if ((value = bd_fwrite(head_p, total, "dict.dat")) == NULL)
		{
			puts("error in bd_fwrite() \n");
			return (char *) 2;
		}

	} else {
		if ((fp_u = fopen(filename_user, "rb")) == NULL) {
			fread(&total, sizeof(total), 1, fp_b);
			head_p = malloc(total * sizeof(*head_p));
			head_p = bd_fread(fp_b, head_p, total);
		} else {
			fread(&total_d, sizeof(total_d), 1, fp_b);
			fread(&total_user, sizeof(total_user), 1, fp_u);

			PRINT(total_user);

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

	puts("\n\t\t\tWelcome enjoy this dictionary\n\n");
	printf("input you word ,exit is quit...  \n");
	while(1) {
		elem_fund = search(head_p, total); //1: 退出，NULL: 没找到,继续找  elem_fund:找到
		if (elem_fund == NULL) {
			add_new_key_bin(filename_user);
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

