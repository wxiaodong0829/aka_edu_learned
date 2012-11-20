#include <stdio.h>
#include <string.h>

#define N 1024

void dollars(char *dest, char const *src)
{
	int len;

	if(dest == NULL || src == NULL)	
	{
		return;
	}

	*dest++ = '$';
	len = strlen(src);

	/*如果数字字符串足够长，复制将出现在小数点左边的数字，在适当的位置添加逗号，如果字符串长度小于3，在小数点前面添加一个‘0’*/
	if(len >= 3)
	{
		int i;
		
		for(i = len - 2; i > 0;)	
		{
			*dest++ = *src++;

			if(--i > 0 && i % 3 == 0)
			{
				*dest++ = ',';
			}
		}
	}
	else
	{
		*dest++ = '0';
	}
	/* 存储小数字，然后存储‘src’中剩余的数字，如果'src'中的数字少于2个数字，用‘0’填充，然后在‘dest’中添加NULL终止符*/
	*dest++ = '.';
	*dest++ = len < 2 ? '0': *src++;
	*dest++ = len < 1 ? '0': *src;
	*dest = 0;
}

int main(int argc, char *argv[])
{
	char src[N];
	char des[N];

	if(argc != 2)
	{
		fprintf(stderr,"Usage:%s string delim subdelim\n", argv[0]);
		return 1;
	}

	strcpy(src, argv[1]);
	dollars(des, src);
	printf("dollars:%s\n", des);
	
	return 0;

}
