#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define N 10 
#define W 800
#define H 600
struct point { int x, y; } P[N];
double adj[N][N];
int mst[N];
double dist(int i, int j)
{
    int dx = P[i].x - P[j].x;
    int dy = P[i].y - P[j].y;
    return sqrt(dx*dx + dy*dy);
}
void init_graph()
{
    int i, j;
    srand(time(NULL));
    for (i=0; i<N; i++) { P[i].x = rand()%W; P[i].y = rand()%H; }
    for (i=0; i<N; i++) {
        adj[i][i] = 0.0;
        for (j=i+1; j<N; j++)
            adj[i][j] = adj[j][i] = (int) dist(i, j);
    }
}
void print_adj(char b[])
{
	int i, j;
	printf("\n");

	for (i = 0; i < N; i++) {
		printf("\n");
		for (j = 0; j < N; j++) {
			printf("%4.0f", adj[i][j]);
		}
	}
}
void print_int_arry(int a[], int r, char b[])
{
	int i;
	printf("\n.PS\n");
	printf("boxwid=.3\n");
	printf("boxht=.3\n");
	printf("arcrad=.1\n");
	printf("box wid .4 \"%s\" invis\n", b);
	for (i = 0; i < r; i++)
	 	printf("box \"%d\"\n", a[i]);
	printf(".PE\n");
	//printf("down\n");
}
void print_double_arry(double a[], int r, char b[])
{
	int i;
	printf(".PS\n");
	printf("boxwid=.3\n");
	printf("boxht=.3\n");
	printf("arcrad=.1\n");
	printf("box wid .4 \"%s\" invis\n", b);

	for (i = 0; i < r; i++) {
	 	printf("box \"%.0f\"\n", a[i]);
	}
	printf(".PE\n");
}
void find_mst()
{
	int k = 0;
	// v:比较与V最近的非党员  w索引非党员和党员   min 保存下一个非党员
    int v, w, min;
	//id[i]: 标记 i 结点, 
	//wt[i]: 当前 i 结点指向下一个党员的最短距离
	//mst[i]:保存i指向的下一个有可能成为党员的结点的编号
    int id[N]; double wt[N+1];
    for (v=0; v<N; v++) { id[v] = 0; wt[v] = W+H; }
	mst[0] = 0; wt[N] = W+H; //min 生成 树初始化 哨兵初始化 
	print_adj("adj");
	for (min=0, k = 0; min!=N; ) {
        id[min] = 1; v = min; min = N;
		print_int_arry(id, N, "id");
		print_int_arry(mst, N, "mst");
		print_double_arry(wt, N, "wt");
        for (w=0; w<N; w++) {
			printf("--------------------------------------------------\n");
			printf("\nmin = %d, w = %d, v = %d\n\n", min, w, v);
            if (id[w]==1) continue;
				printf("\nw = %d,     wt[w] = %.0f,    adj[v][w] = %.0f,    v = %d\n\n", w, wt[w], adj[v][w], v);
            if (wt[w]>adj[v][w]) {   
				wt[w]=adj[v][w]; 
				mst[w] = v; 
				printf("\nw = %d, wt[w] = %f, mst[w]=v= %d        mst[w] <-- v\n\n", w, wt[w], v);
			}
			printf("\nmin = %d, w = %d,   wt[min] = %.0f,  wt[w] = %.0f\n\n", min, w ,wt[min], wt[w]);
            if (wt[min]>wt[w]) {
				min = w;
				printf("\nmin =  w = %d,		          	min <-- w\n\n", w ,wt[min], wt[w]);
			}
        }
    }
}
void show_mst()
{
    int i;
    printf(".PS 6 5\n");
    printf("circlerad=4\n");
    for (i=1; i<N; i++) {
        printf("C1: circle at %d,%d fill\n",
                P[i].x, P[i].y);
        printf("C2: circle at %d,%d fill\n",
                P[mst[i]].x, P[mst[i]].y);
        printf("line from C1 to C2 chop\n");
    }
    printf(".PE\n");
}
int main()
{
  //  printf(".PS\n");
//	printf("0\n");
    init_graph();
     find_mst();
   // printf(".PE\n");
//    show_mst();
    return 0;
}
