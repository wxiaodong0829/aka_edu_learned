#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct usr
{
	char *usr_name;
	struct sockaddr_in addr;
	int is_online;
	struct usr *next;
}usr_t;

usr_t *head = NULL;

usr_t *new_node(const char *usr_name)
{
	usr_t *p;

	p = (usr_t *)malloc(sizeof(usr_t));
	if(p == NULL)
		return NULL;
	p->usr_name = (char *)malloc(sizeof(char) * (strlen(usr_name) + 1));
	strcpy(p->usr_name, usr_name);
	p->is_online = 0;
	p->next = NULL;
	memset(&p->addr, 0, sizeof(p->addr));

	return p;
}

int insert(const char *usr_name)
{
	usr_t *p, *q;

	p = new_node(usr_name);
	if(p == NULL)
		return -1;
	if(head == NULL){
		head = p;
		return 0;
	}
	for(q = head; q->next != NULL; q = q->next);
	q->next = p;

	return 0;
}

int is_equal(struct sockaddr_in *p, struct sockaddr_in *q)
{
	return p->sin_family == q->sin_family && p->sin_port == q->sin_port && p->sin_addr.s_addr == q->sin_addr.s_addr;
}

usr_t *search_by_addr(struct sockaddr_in *addr)
{
	usr_t *p;

	for(p = head; p != NULL; p = p->next)
		if(is_equal(&p->addr, addr))
			return p;

	return NULL;
}

usr_t *search_by_name(const char *usr_name)
{
	usr_t *p;

	for(p = head; p != NULL; p = p->next)
		if(strcmp(p->usr_name, usr_name) == 0)
			break;
	return p;
}

void print(void)
{
	usr_t *p;
	char ip[20];

	for(p = head; p != NULL; p = p->next){
		printf("name : %s, ", p->usr_name);
		if(p->is_online == 0)
			printf("out-of-line, ");
		else
			printf("online, ");
		inet_ntop(AF_INET, &p->addr.sin_addr.s_addr, ip, 20);
		printf("ip : %s, ", ip);
		printf("port : %u\n", ntohs(p->addr.sin_port));
	}
}

void destroy(void)
{
	usr_t *p, *q;

	for(p = head; p != NULL; p = q){
		q = p->next;
		free(p->usr_name);
		free(p);
	}

	head = NULL;
}

int get_usr_info(const char *filename)
{
	FILE *fp;
	char buf[1024];

	fp = fopen(filename, "r");
	if(fp == NULL)
		return -1;
	while(fgets(buf, 1024, fp)){
		buf[strlen(buf) - 1] = '\0';
		insert(buf);
	}

	fclose(fp);

	return 0;
}

int sock_init(in_port_t port, const char *ip)
{
	int sfd;
	struct sockaddr_in serv_addr;

	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sfd == -1)
		return -1;

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &serv_addr.sin_addr.s_addr);

	if(bind(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		return -1;

	return sfd;
}

int main(void)
{
	int sfd, n;
	char buf[1024];
	usr_t *p; socklen_t len;
	struct sockaddr_in cli_addr;

	get_usr_info("usr_info.txt");
	sfd = sock_init(8000, "127.0.0.1");
	
	while(1){
		len = sizeof(struct sockaddr_in);
		n = recvfrom(sfd, buf, 1024, 0, 
			(struct sockaddr *)&cli_addr, &len);
		buf[n] = '\0';
		
		if(strncmp(buf, "syn", 3) == 0){ /* login */
			char *name;

			name = strstr(buf, " ");
			name++;	
			p = search_by_name(name);
			if(p == NULL)
				sendto(sfd, "fail", strlen("fail"), 0,
					(struct sockaddr *)&cli_addr, sizeof(cli_addr));
			else{
				p->is_online = 1;
				p->addr = cli_addr;
				sendto(sfd, "OK", strlen("OK"), 0,
					(struct sockaddr *)&cli_addr, sizeof(cli_addr));
			}
#ifdef DEBUG
			print();
#endif

		}else if(strncmp(buf, "fin", 3) == 0){ /* logout */
			char *name;

			name = strstr(buf, " ");
			name++;	
			p = search_by_name(name);
			if(p == NULL)
				sendto(sfd, "fail", strlen("fail"), 0,
					(struct sockaddr *)&cli_addr, sizeof(cli_addr));
			else{
				p->is_online = 0;
				memset(&p->addr, 0, sizeof(p->addr));
				sendto(sfd, "OK", strlen("OK"), 0,
					(struct sockaddr *)&cli_addr, sizeof(cli_addr));
			}
#ifdef DEBUG
			print();
#endif
		}else{ /* somebody talk */
			char msg[32];			

			p = search_by_addr(&cli_addr);
			if(p == NULL)
				continue;
			
			sprintf(msg, "%s say : ", p->usr_name);
			for(p = head; p != NULL; p = p->next){
				if(p->is_online){
					n = sendto(sfd, msg, strlen(msg), 0,
						(struct sockaddr *)&p->addr, sizeof(p->addr));
					n = sendto(sfd, buf, strlen(buf), 0,
						(struct sockaddr *)&p->addr, sizeof(p->addr));
				}
			}
		}

		printf("one data over...\n");
	}

	destroy();
	
	return 0;
}
