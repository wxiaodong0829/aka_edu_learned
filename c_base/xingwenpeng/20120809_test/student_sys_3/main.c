/*************************************************************************
    > File Name: read_from_in_to_link.c
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月08日 星期三 09时32分41秒
 ************************************************************************/

#include "link.h"

//#ifdef DEBUG
int main(int argc, char *argv[])
{
	char name[LEN] = "bbb";
	int n = 1;
	float chgrade = 20.0;
	void *p = NULL;
	p = (void *)&chgrade;

	FILE *fp;
	node_t *link_head = NULL;
	node_t *tmp;
	init_head(&link_head);
	//if ((fp = link_read_file(argv[1], &link_head)) == NULL) {
	if ((fp = link_read_file("stufile.txt", &link_head)) == NULL) {
		perror("fopen in: ");
		exit(-1);
	}
	
	//link_search(p, node_t, name, link_head, tmp);
	//link_remove(p, node_t, chgrade, link_head, tmp);
	//printf("%p: %s\n", tmp, tmp->name);

	//link_search(p, node_t, id, link_head, tmp);
	//link_remove(p, node_t, id, link_head, tmp);
	//printf("%p: %d\n", tmp, tmp->id);

	link_print(link_head);

	link_sort(link_head, node_t, id, link_head);
	printf("\nid:\n");
	link_print(link_head);

	link_sort(link_head, node_t, name, link_head);
	printf("\nname:\n");
	link_print(link_head);

	link_sort(link_head, node_t, chgrade, link_head);
	printf("\nchgrade:\n");
	link_print(link_head);

	link_fclose(fp);
	link_destroy(&link_head);

	return 0;
}
//#endif
