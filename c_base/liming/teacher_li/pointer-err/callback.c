void test(void (*p)(void))
{
    //p(); (*p)();
    p();

    return;
}

void print(void)
{
    printf("hello\n");
}

int main(void)
{
    void (*pf)(void);

    pf = print;

    //pf();

    test(pf);
}

