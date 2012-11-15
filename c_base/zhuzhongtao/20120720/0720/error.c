//void f(char a[])
void f(char *a)
{
    a++;
}
int main()
{
    char s[] = "hello";
    char *p = s;
//    s++;
    f(s);
    return 0;
}
