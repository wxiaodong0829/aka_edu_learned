#include <stdio.h>

#if 0
int max(int num[], int n)
{
    int max = 0;
    int i;

    for (i = 0; i < n; i++)
    {
        if (max < num[i])
            max = num[i];
    }

    return max;
}
#endif

void * max(void * data[], int n, int size, int (*cmp)(void *a, void *b))
{
    void * ret;
    int i;

    ret = &data[0];
    for (i = 1; i < n; i++)
    {
//        printf("i = %d\n", i);
//        printf("data[i] = %f\n", (double)data[i]);
        if (cmp(ret, (char *)data + i * size) < 0)
        {
            ret = (char *)data + i * size; 
            //printf("if i = %d\n", i);
        }
    }

    return ret;
}

//int int_cmp(int a, int b)
int int_cmp(void * a, void * b)
{
    int ta;
    int tb;

    ta = *(int *)a;
    tb = *(int *)b;
    return (ta - tb);
}

//int double_cmp(double a, double b)
int double_cmp(void * a, void * b)
{
    double ta;
    double tb;

    ta = *(double *)a;
    tb = *(double *)b;
    //printf("d cmp %f:%f\n", ta, tb);
    return (int)(ta - tb);
}

//int str_cmp(char * a, char * b)
int str_cmp(void * a, void * b)
{
    return strcmp(*(char **)a, *(char **)b);
}

int main(void)
{
    int n[5] = {8, 2, 3, 1, 5};
    double d[5] = {8.1, 2.5, 3.3, 10, 5.2};
    char * name[5] = {"zhang", "li", "wang", "zhao", "sun"};

    void * ret;

    ret = max((void *)n, 5, sizeof(int), int_cmp);
    printf("ret = %d\n", *(int *)ret);

    ret = max((void *)d, 5, sizeof(double), double_cmp);
    printf("ret = %f\n", *(double *)ret);

    ret = max((void *)name, 5, sizeof(char *), str_cmp);
    printf("ret = %s\n", *(char **)ret);


    return 0;
}
