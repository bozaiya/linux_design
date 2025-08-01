/*列出当前运行的进程及显示每个进程的详细信息*/
#include "list_pid.h"

void function_list()
{
    int c,list_flag = 1;

    printf("---1.列出用户进程---\n");
    printf("---2.列出其他---\n");
    printf("---3.退出---\n");
    scanf("%d", &c);
    
    while (list_flag)
    {
        
    switch (c)
    {
    case 1:
        pid_t pid;
        if ((pid = vfork()) == 0)
        {
            char *argv[] = {"ps", "-l", NULL};
            execvp("ps", argv);
        }
        break;
    case 2:
        DIR *dir;
        struct dirent *entry;

        dir = opendir("/proc");
        if (dir == NULL)
        {
            printf("无法打开 /proc 目录\n");
            exit(1);
        }

        printf("%-8s %-20s %-10s\n", "PID", "进程名", "状态");

        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_DIR)
            {
                char path[512];
                FILE *file;
                char line[512];
                char name[512];
                char status[512];
                int pid;

                // 构建进程信息文件的路径
                snprintf(path, sizeof(path), "/proc/%s/status", entry->d_name);
                file = fopen(path, "r");

                if (file)
                {
                    // 读取进程信息文件的内容
                    while (fgets(line, sizeof(line), file))
                    {
                        if (strncmp(line, "Name:", 5) == 0)
                        {
                            sscanf(line, "%*s %s", name);
                        }
                        if (strncmp(line, "State:", 6) == 0)
                        {
                            sscanf(line, "%*s %s", status);
                        }
                        if (strncmp(line, "Pid:", 4) == 0)
                        {
                            sscanf(line, "%*s %d", &pid);
                        }
                    }

                    fclose(file);

                    // 输出进程信息
                    printf("%-8d %-20s %-10s\n", pid, name, status);
                }
            }
        }

        closedir(dir);
        break;

    case 3:
        list_flag = 0;
        break;
        
    default:
        break;
    }
    /*
    pid_t pid = vfork();
    switch (pid)
    {
    case -1:
        perror("vfork failed");
        break;
    case 0:
        char *argv[] = {"ps", "-l", NULL};
        execvp("ps", argv);
    default:
        break;
    }
    */
    }
    
}