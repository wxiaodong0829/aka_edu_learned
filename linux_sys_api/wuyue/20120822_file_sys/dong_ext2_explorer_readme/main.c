#include "common.h"

int main(int argc, char *argv[])
{
	FILE *fp; int i, j; 
	char buf[1024 * BLKSZ_1K];
	int blksz = BLKSZ_1K;
	u32 *index; u8 *rb, *blk_end;
	int rlen, nlen; char *name;

	if(argc != 2) 
		err_usr("wrong command\n");

	fp = fopen(argv[1], "r");
	if(fp == NULL) 
		err_sys("fail to fopen");
	fread(buf, sizeof(char), 1024 * BLKSZ_1K, fp);

	// 获取根目录inode管理结构中的index数组
	index = root_index(buf, BLKSZ_1K);
	for(i = 0; i < 12; i++){
		if(!index[i])
			continue;
		//求index[i]号的盘块的地址
		rb = (u8 *)blk_to_addr(buf, BLKSZ_1K, index[i]);
		blk_end = rb + BLKSZ_1K; //此块的末地址
		while(rb < blk_end){
			rlen = *((u16 *)(rb + 4));//根据存放根目录内容的盘块的地址，偏移到存放此条目录项长度的地址，并取出此目录项的长度.
			nlen = *((u8 *)(rb + 6));//求目录项中文件名的长度.
			name = (u8 *)(rb + 8);//求文件名首地址.
			
			for(j = 0; j < nlen; j++)
				putchar(name[j]);
			putchar('\n');
			rb += rlen;
		}
	}

	fclose(fp);

	return 0;
}
