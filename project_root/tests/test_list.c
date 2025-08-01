#include <stdio.h>
#include <unistd.h>

int main()
{
    char *argv[] = {"ps", "-l", NULL};
    execvp("ps", argv);
}