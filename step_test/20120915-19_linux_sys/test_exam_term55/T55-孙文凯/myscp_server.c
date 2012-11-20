#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "myscp.h"



int main(void)
{
    int lfd, cfd, fd, n;
    char buf[N], path[N];
    struct sockaddr_in serv_addr;

    lfd = socket(AF_INET, SOCK_STREAM, 0);  /*    创建套接字  */
    if (lfd == -1)
        err_sys("socket error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

    n = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));  /*    绑定端口    */
    if (n == -1)
        err_sys("bind error");
    n = listen(lfd, 20);  /*   注册   */
    if (n == -1)
        err_sys("listen error");

    memset(path, 0, sizeof(path));
    memset(buf, 0, sizeof(buf));

    while (1) {
        cfd = accept(lfd, NULL, NULL);  /*   阻塞等待链接  */
        if (cfd == -1)
            err_sys("accept error");

        read(cfd, buf, N);  /*    读取客户端的请求   */

        if (strncmp(buf, DOWNLOAD, 1) == 0) { /*     如果是下载    */
            write(cfd, OK, 1);  /*    给客户端回应OK   */
            read(cfd, path, N);  /*   读取要下载的文件名及其路径    */

            fd = open(path, O_RDONLY);  /*   只读打开文件  */
            if (fd != -1) {  /*  打开成功，回应客户端OK    */
                write(cfd, OK, 1);
            }else {  /*   打开失败，回应ERR并continue   */
                write(cfd, ERR, 1);
                close(cfd);
                continue;
            }

            while ((n = read(fd, buf, N)))  /*   循环给客户端发送文件内容   */
                write(cfd, buf, n);

            memset(path, 0, sizeof(path));

            close(cfd);
            close(fd);
            continue;

        }else if (strncmp(buf, UPLOAD, 1) == 0) { /*     如果是上传     */
            write(cfd, OK, 1);  /*   回应客户端OK    */
            read(cfd, path, N);  /*   读取要上传的文件名及其路径   */

            fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);  /*  创建并打开文件  */
            if (fd == -1) {  /*   打开失败，回应ERR并continue  */
                write(cfd, ERR, 1);
                close(cfd);
                continue;
            }else
                write(cfd, OK, 1);  /*   打开成功，回应OK   */

            while ((n = read(cfd, buf, N)))  /*   循环读取上传的内容   */
                write(fd, buf, n);

            memset(path, 0, sizeof(path));

            close(cfd);
            close(fd);
            continue;

        }else {  /*  客户端请求出错,回应ERR并continue   */
            write(cfd, ERR, 1);
            close(cfd);
            continue;
        }

    }

    return 0;
}
