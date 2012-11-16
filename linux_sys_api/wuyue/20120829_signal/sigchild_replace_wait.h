/*************************************************************************
    > File Name: sigchild_replace_wait.h
    > Author: wxiaodong
    > Mail  : wxiaodong0829@163.com 
    > 自由  谐作   创造   沟通
    > Created Time: 2012年08月29日 星期三 21时47分03秒
 ************************************************************************/
#ifndef SIGCHILD_REPLACE_WAIT_
#define SIGCHILD_REPLACE_WAIT_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "err.h"


int init_sig_child(int signo, int flag, struct sigaction *old);

int recover_sigaction(int signo, struct sigaction *old);


#endif
