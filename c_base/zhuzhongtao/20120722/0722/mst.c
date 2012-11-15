#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define N 200
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
            adj[i][j] = adj[j][i] = dist(i, j);
    }
}
void find_mst()
{
    int v, w, min;
    int id[N]; double wt[N+1];
    for (v=0; v<N; v++) { id[v] = 0; wt[v] = W+H; }
    mst[0] = 0; wt[N] = W+H;
    for (min=0; min!=N; ) {
        id[min] = 1; v = min; min = N;
        for (w=0; w<N; w++) {
            if (id[w]==1) continue;
            if (wt[w]>adj[v][w])
            {   wt[w]=adj[v][w]; mst[w] = v; }
            if (wt[min]>wt[w]) min = w;
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
    init_graph();
    find_mst();
    show_mst();
    return 0;
}
