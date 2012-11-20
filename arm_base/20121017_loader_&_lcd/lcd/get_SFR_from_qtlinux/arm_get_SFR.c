/*************************************************************************
    > File Name: arm_get_SFR.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年10月17日 星期三 14时45分15秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#define BASE 0xF8000000   // lcd SFR 

int main(void)
{
	int fd;
	unsigned char *vmem;
	int i;
	fd = open("/dev/mem", O_RDWR);
	if (fd < 0) {
		perror("dev/mem open");
		exit(-1);
	}
	vmem = mmap(0, 0x1000, PROT_READ, MAP_SHARED, fd, BASE);

	i = 0; 
	while (i < 0x1000) {
		printf("(*(volatile unsigned int *)%x) = %x\n", BASE + i, *(vmem+i));
		i += 4;
	}
	munmap(vmem, 0x1000);
	close(fd);
	return 0;
}

