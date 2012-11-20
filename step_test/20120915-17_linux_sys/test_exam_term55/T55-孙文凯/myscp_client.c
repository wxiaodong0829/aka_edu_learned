#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "myscp.h"


int main(int argc, char *argv[])
{
    int sfd, fd, n;
    int flags_down, flags_up;
    struct sockaddr_in serv_addr;
    char buf[N], path[N], serv_path[N];
    char ip[24];
    char flags[1];
    char *p;
    if (argc != 3 || strcmp(argv[0], "./myscp") != 0)
        err_usr("wrong command");

    /*     判断是上传还是下载     */
    flags_down = match(argv[1]);
    flags_up = match(argv[2]);
    if (flags_down == -1 || flags_up == -1)  // 输入的命令行参数有误
        err_usr("wrong command");

    if (flags_down == 1)
        strcpy(buf, argv[1]);
    else if (flags_up == 1)
        strcpy(buf, argv[2]);
    p = strtok(buf, ":");
    strcpy(ip, p);  /*     把输入的服务器ip解析出来放到字符数组ip[24]中    */

    sfd = socket(AF_INET, SOCK_STREAM, 0);  /*   创建套接字   */
    if (sfd == -1)
        err_sys("socket error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, ip, &serv_addr.sin_addr.s_addr);

    n = connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));  /*    创建链接    */
    if (n == -1)
        err_sys("connect error");

    if (flags_down == 1 && flags_up == 0) { /*    如果是下载     */
        write(sfd, DOWNLOAD, 1); /*    给服务器发送下载信号    */

        read(sfd, flags, 1); /*    读取服务器的回应    */
        if (strncmp(flags, OK, 1) == 0) { /*    若服务器正确收到信号,开始解析命令行参数   */

            strcpy(path, argv[2]);
            if (path[strlen(path) - 1] == '/')
                path[strlen(path) - 1] = '\0';
            p = strrchr(argv[1], '/');
            strcat(path, p);
            fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);   /*    创建并打开要下载文件的拷贝   */
            if (fd == -1)
                err_sys("open error");

            p = strstr(argv[1], ":") + 1;
            strcpy(serv_path, p);   /*      经过拼接得到完整路径名     */
            write(sfd, serv_path, strlen(serv_path)); /*     给服务器发送要下载的文件名及其路径    */

            read(sfd, flags, 1); /*    读取服务器的回应     */
            if (strncmp(flags, OK, 1) == 0) { /*    如果服务器正常打开文件，则开始下载   */
                while((n = read(sfd, buf, N)))
                    write(fd, buf, n);
            }else if (strncmp(flags, ERR, 1) == 0) { /*   服务器回应出错  */
                err_usr("it is a dir or no such file");
            }

        }else if (strncmp(flags, ERR, 1) == 0) /*      服务器回应出错     */
            err_sys("something error");

    }else if (flags_down == 0 && flags_up == 1) {  /*    如果是上传     */
        write(sfd, UPLOAD, 1);  /*   给服务器发送上传信号  */
        read(sfd, flags, 1); /*    读取服务器回应    */

        if (strncmp(flags, OK, 1) == 0) {  /*   服务器回应OK   */

            strcpy(path, argv[1]);
            fd = open(path, O_RDONLY);  /*    打开要上传的文件    */
            if (fd == -1)
                err_usr("file error");

            p = strstr(argv[2], ":") + 1;
            strcpy(serv_path, p);
            if (serv_path[strlen(serv_path) - 1] != '/') {
                serv_path[strlen(serv_path)] = '/';
                serv_path[strlen(serv_path) + 1] = '\0';
            }
            p = strrchr(argv[1], '/');
            if (p == NULL)
                p = argv[1];
            else
                p = p + 1;
            strcat(serv_path, p);
            write(sfd, serv_path, strlen(serv_path)); /*   给服务器发送上传文件的路径及文件名    */

            read(sfd, flags, 1);  /*    读取服务器的回应    */
            if (strncmp(flags, OK, 1) == 0) {  /*   服务器回应OK,开始上传   */
                while((n = read(fd, buf, N)))
                    write(sfd, buf, n);

            }else if (strncmp(flags, ERR, 1) == 0) {  /*  服务器回应出错*/
                err_usr("file error");
            }

        }else if (strncmp(flags, ERR, 1) == 0) /*     服务器回应出错    */
            err_sys("something error");

    }
    close(sfd);
    close(fd);

    return 0;
}
