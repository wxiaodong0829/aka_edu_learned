

/* 0:read, 1:write, 2:except */
int is_readable(int fd, int witch)
{
	fd_set set;
	int n;
	struct timeval t = {0, 0};
	fd_set *r = NULL, *w = NULL, *e = NULL;

	FD_ZERO(&set);
	FD_SET(fd, &set);
	switch(witch){
		case 0: r = &set; break;
		case 1: w = &set; break;
		case 2: e = &set; break;
		default: return -1;
	}
	n = select(fd + 1, r, w, e, &t);	
	
	return n;
}

int read_timeout(int fd, char *buf, int size, 
	int timeout)
{
	fd_set set;
	struct timeval t;
	int n;

	FD_ZERO(&set);
	FD_SET(fd, &set);
	t.tv_sec = timeout; 
	t.tv_usec = 0;
	
	n = select(fd + 1, &set, NULL, NULL, &t);
	if(n == 1)
		n = read(fd, buf, size);
	else{
		n = -1;
		errno = ETIMEDOUT;	/* 让这个函数像系统函数一样，设置　errno , 专业　*/
	}

	return n;
}








