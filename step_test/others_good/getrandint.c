
void get_rand_int(int a[], int l, int r, int size)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < size; i++)
		a[i] = rand() % (r - l + 1) + l;
}
