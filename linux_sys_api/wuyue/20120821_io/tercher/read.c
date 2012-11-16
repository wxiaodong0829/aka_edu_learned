#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int main(void)
{
    char buf[1024];
    int n;
    int flags;

    flags = fcntl(0, F_GETFL);
    flags = flags | O_NONBLOCK;
    fcntl(0, F_SETFL, flags); 
again:
    n = read(0, buf, 1024);
    if(n == -1){
        if(errno == EWOULDBLOCK){
            printf("no data...\n");
            sleep(3);
            goto again;
        }else
            return -1;
    }
    write(1, buf, n);

    return 0;
}
