#ifndef MYSCP_H_
#define MYSCP_H_


#define UPLOAD "0"
#define DOWNLOAD "1"
#define OK "1"
#define ERR "0"
#define SERV_IP "127.0.0.1"
#define SERV_PORT 8000
#define N 1024

void err_sys(const char *str);
void err_usr(const char *str);
int match(const char *str);

#endif
