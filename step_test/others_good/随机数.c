void init()
{
	int i;
	srand(time(NULL));
	for(i=1;i<N;i++)
		num[i]=rand()%N;
}
