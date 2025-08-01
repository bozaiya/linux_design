/*
编写一个多线程多进程的程序
要求创建三个子进程，每个子进程都分别创建两个线程，所有进程和线程都输出自己的ID。
*/
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

void *printId(void *arg)
{
    cout << "pthread id is: " << pthread_self << endl;
}

int main()
{
    pid_t pid;

    for (int i = 0; i < 2; i++)
    {
        if (pid = vfork() == -1)
        {
            perror("vfork error");
        }

        cout << "this process id is: " << getpid() << endl;

        if (pid == 0)
        {
            pthread_t ntid;
            // 创建线程
            for (int i = 0; i < 2; i++)
            {
                int ret = pthread_create(&ntid, NULL, printId, NULL);
                if (ret != 0)
                {
                    cout << "pthread_create error" << endl;
                    exit(1);
                }
            }
        }
    }
    sleep(1);
    exit(0);

    return 0;
}