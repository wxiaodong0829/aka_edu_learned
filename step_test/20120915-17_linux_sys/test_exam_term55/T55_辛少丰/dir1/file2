#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void showinfo(void)
{
	printf("Please select the option:\n");
	printf("1.Display all student's info\n");
	printf("2.Sort by average\n");
	printf("3.Insert a new info\n");
	printf("4.Delete a record\n");
	printf("5.Quit\n");
	printf("Please input your choice:");
}
void showstu(link_t head)
{
	link_t cur;
	int i = 1;
	printf("seq  ID   %8s    CHGRADE  MATHGRADE  AVERAGE\n", "NAME");
	printf("---------------------------------------------------\n");
	for(cur = head; cur; cur = cur->next)
	{
		printf("%3d:%3d %10s %8.1f %8.1f %8.1f\n", i, cur->ID, cur->name, cur->chgrade, cur->mathgrade, cur->average);
		i++;
	}
	printf("---------------------------------------------------\n");

}
int main(int argc, char *argv[])
{
	int selnum;
	link_t head_show = NULL, head_sort = NULL;
	int flagbyaverage = 1, ins_del_flag = 0, firstsort = 1;
	if(argc != 2)
	{
		fprintf(stderr, "Usage argument:./app \"filename\"\n");
		exit(1);
	}

	head_show = creat(argv[1], !flagbyaverage, head_show);
	while(1)
	{
		showinfo();
		scanf("%d", &selnum);
		switch(selnum)
		{
			case 1:	showstu(head_show);
					break;

			case 2: 
                    if(ins_del_flag == 1){
                        link_destroy(head_sort);
                        head_sort = NULL;
                    }
                    if(firstsort == 1 || ins_del_flag == 1){
                        head_sort = creat(argv[1], flagbyaverage, head_sort);
                        ins_del_flag = 0;
                        firstsort = 0;
                    }
					showstu(head_sort);
					break;

			case 3:	head_show = insertrecord(argv[1], head_show);
                    ins_del_flag = 1;
					break;
           
			case 4: head_show = deleterecord(argv[1],head_show);
                    ins_del_flag = 1;
					showstu(head_show);
					break;
            
			case 5: if(head_show)
                        link_destroy(head_show);
                    if(head_sort)
                        link_destroy(head_sort);
					return 0;

			default: break;
		}
	}
	return 0;
}
