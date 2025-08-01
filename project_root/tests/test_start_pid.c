#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#define MAXSIZE 100

int main()
{
    int exitstatus = 1;
    char command[MAXSIZE];

    while (exitstatus)
    {
        printf("\n$~:");
        scanf("%s", command);
        getchar();
        if (strcmp(command, "exit") == 0)
        {
            exitstatus = 0;
            continue;
        }
        else
        {
            pid_t pid = vfork();
            switch (pid)
            {
            case -1:
                perror("vfork failed");
                break;
            case 0:
                // exec函数实现
                execlp(command, command, NULL);
            default:
                break;
            }
        }
    }
    printf("success\n");
    execlp("ps", "-l", NULL);
}