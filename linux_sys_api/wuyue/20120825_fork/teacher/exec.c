#include <unistd.h>

int main(void)
{
    char *myargv[] = {"ls", "-a", NULL};

    execvp("ls", myargv);

    return 0;
}
