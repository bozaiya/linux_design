/*启动、暂停、终止和监视进程*/
#include "operate_pid.h"

void function_operate()
{
    int choice = 0;
    int flag = 1;
    int exitstatus = 1;
    while (flag)
    {
        printf("---1.开启进程---\n");
        printf("---2.暂停进程---\n");
        printf("---3.终止进程---\n");
        printf("---4.监视进程---\n");
        printf("---5.退出---\n");
        printf("~: ");

        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            // 1、启动进程
            char command[MAXSIZE];
            printf("\n(输入quit退出)$~:");
            while (exitstatus)
            {
                scanf("%s", command);
                getchar();

                if (strcmp(command, "quit") == 0)
                {
                    exitstatus = 0;
                    continue;
                }

                pid_t pid;
                if ((pid = vfork()) == 0)
                {
                    execlp(command, command, NULL);
                    exit(EXIT_SUCCESS);
                }
                else
                {
                    printf("$~:");
                }
            }

            break;

        case 2:
            // 2、暂停进程
            char str_1[5];
            printf("please enter pid_id: ");
            scanf("%s", str_1);

            pid_t pid_1;
            if ((pid_1 = vfork()) == 0)
            {
                execlp("kill", "kill", "-19", str_1, NULL);
            }

            break;

        case 3:
            // 3、终止进程
            char str_2[5];
            printf("please enter pid_id: ");
            scanf("%s", str_2);

            pid_t pid_2;
            if ((pid_2 = vfork()) == 0)
            {
                execlp("kill", "kill", "-9", str_2, NULL);
            }

            break;

        case 4:
            // 4、监视进程
            /*
            char str_3[5];
            printf("please enter pid_id: ");
            scanf("%s", str_3);

            pid_t pid_3;
            if ((pid_3 = vfork()) == 0)
            {
                execlp("top", "-p", str_3, NULL);
            }
            */
            int numProcesses;
            printf("请输入要监听的进程数量：");
            scanf("%d", &numProcesses);

            MonitoredProcess *processes = (MonitoredProcess *)malloc(numProcesses * sizeof(MonitoredProcess));

            char input[256];
            pthread_t *threads;
            while (1)
            {
                // 获取要监听的进程ID
                printf("请输入要监听的进程ID：\n");
                for (int i = 0; i < numProcesses; i++)
                {
                    printf("进程 %d：", i + 1);
                    scanf("%d", &(processes[i].pid));
                    processes[i].isRunning = 1;
                }

                // 创建监听线程
                threads = (pthread_t *)malloc(numProcesses * sizeof(pthread_t));
                for (int i = 0; i < numProcesses; i++)
                {
                    pthread_create(&threads[i], NULL, monitorProcess, (void *)&processes[i]);
                }

                sleep(1);
                printf("输入exit退出或按任意键继续\n");

                bzero(&input, sizeof(input));
                scanf("%s", input);

                if (strcmp(input, "exit") == 0)
                {
                    break;
                }
            }

            // 取消监听线程
            for (int i = 0; i < numProcesses; i++)
            {
                pthread_cancel(threads[i]);
            }

            // 等待线程结束
            for (int i = 0; i < numProcesses; i++)
            {
                pthread_join(threads[i], NULL);
            }

            printf("所有进程监听结束\n");

            free(processes);
            free(threads);
            break;

        case 5:
            flag = 0;
            break;
        }

        if (choice < 5 || choice > 1)
        {
            printf("***success***\n\n");
        }
    }
}