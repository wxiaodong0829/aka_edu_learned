#include <aio.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void my_handler(int signo, siginfo_t *info, void *context)
{
	struct aiocb *p;
	int n;
	char *str;

	p = (struct aiocb *)info->si_value.sival_ptr;
	n = aio_return(p);
	str = (char *)p->aio_buf;
	write(STDOUT_FILENO, str, n);

}

void tfn(union sigval arg)
{
	struct aiocb *p;
	int n;
	char *str;

	p = (struct aiocb *)arg.sival_ptr;
	n = aio_return(p);
	str = (char *)p->aio_buf;
	write(STDOUT_FILENO, str, n);

}

int main(void)
{
	struct aiocb cb;
	struct sigaction act;
	char buf[1024];

	memset(&act, 0, sizeof(act));
	act.sa_sigaction = my_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);

	memset(&cb, 0, sizeof(cb));
	cb.aio_fildes = STDIN_FILENO;
	cb.aio_buf = buf;
	cb.aio_nbytes = 1024;

#if 0
	cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
	cb.aio_sigevent.sigev_signo = SIGUSR1;
	cb.aio_sigevent.sigev_value.sival_ptr = (void *)&cb;
#else
	cb.aio_sigevent.sigev_notify = SIGEV_THREAD;
	cb.aio_sigevent.sigev_notify_function = tfn;
	cb.aio_sigevent.sigev_notify_attributes = NULL;
	cb.aio_sigevent.sigev_value.sival_ptr = (void *)&cb;

#endif
	

	aio_read(&cb);
	while(1);

	return 0; 
}
