#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>

#define MAXSIZE 100

// 监控进程的结构体
typedef struct
{
    pid_t pid;
    int isRunning;
} MonitoredProcess;

// 监控线程的函数
void *monitorProcess(void *arg)
{
    MonitoredProcess *process = (MonitoredProcess *)arg;

    while (1)
    {
        // 使用kill函数检查进程状态
        int result = kill(process->pid, 0);

        if (result == -1)
        {
            // 进程不存在或无法访问
            process->isRunning = 0;
        }
        else
        {
            process->isRunning = 1;
        }

        if (!process->isRunning)
        {
            printf("进程 %d 已退出\n", process->pid);
            break;
        }

        // 获取进程详细信息
        char procPath[256];
        snprintf(procPath, sizeof(procPath), "/proc/%d/stat", process->pid);

        // 打开进程状态文件
        FILE *file = fopen(procPath, "r");
        if (file == NULL)
        {
            printf("无法打开进程 %d 的状态文件\n", process->pid);
            break;
        }

        char line[256];
        if (fgets(line, sizeof(line), file))
        {
            // 解析并显示进程详细信息
            printf("进程ID\t进程名\t状态\t父进程ID\n");

            char *token = strtok(line, " ");
            int counter = 0;
            while (token != NULL && counter < 4)
            {
                printf("%s\t", token);
                token = strtok(NULL, " ");
                counter++;
            }
            printf("\n");
        }

        fclose(file);

        sleep(5);
    }

    return NULL;
}

